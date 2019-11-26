#include "CSerializer.h"

#include "CMsgTypesFromServer.h"
#include "CGameState.h"

#include <mutex>

CSerializer::CSerializer() :
	m_battlefield({ 0 }),
	m_greenSoldier({ 0 }),
	m_blueSoldier({ 0 })
{

}



CSerializer::~CSerializer()
= default;



// Message structure in bytes:
	// [0] - msg type
	// [1] - advanced type
	// [2] - number of objects
	// bytes 3, 4, 5, 6 holds struct size
	// [3] - number of thousands
	// [4] - number of hundreds
	// [5] - number of tens
	// [6] - number of units
	// [...] - data
void CSerializer::translateMsg(std::vector<char> msg)
{
	switch (msg[0]) {
	case BATTLEFIELD_MSG_TYPE:
		translateBattlefieldMsg(msg);
		break;
	case SOLDIER_MSG_TYPE:
		translateSoldierMsg(msg);
		break;
	case BULLETS_MSG_TYPE:
		translateBulletsMsg(msg);
		break;
	}
}



void CSerializer::translateBattlefieldMsg(std::vector<char> msg)
{
	char* buffer = new char[BATTLEFIELD_STRUCT_SIZE];
	for (int i = 7; i < msg.size(); i++) {
		buffer[i - 7] = msg[i];
	}

	BattlefieldStruct* battlefield = reinterpret_cast<BattlefieldStruct*>(buffer);
	setBattlefield(battlefield);

	//delete(battlefield);
	//delete[](buffer);
}



void CSerializer::translateSoldierMsg(std::vector<char> msg)
{
	char* buffer = new char[SOLDIER_STRUCT_SIZE];
	for (int i = 7; i < msg.size(); i++) {
		buffer[i - 7] = msg[i];
	}

	SoldierStruct* soldier = reinterpret_cast<SoldierStruct*>(buffer);

	switch (msg[1]) {
	case GREEN_SOLDIER:
		setGreenSoldier(soldier);
		break;
	case BLUE_SOLDIER:
		setBlueSoldier(soldier);
		break;
	}

	//delete(soldier);
	//delete[](buffer);
}



void CSerializer::translateBulletsMsg(std::vector<char> msg)
{
	std::vector<BulletStruct*> bullets;
	char nOfBullets = msg[2];
	for (int bulletN = 0; bulletN < nOfBullets; bulletN++) {
		char* buffer = new char[BULLET_STRUCT_SIZE];

		int pos = bulletN * BULLET_STRUCT_SIZE + 7;
		for (int i = 0; i < BULLET_STRUCT_SIZE; i++) {
			buffer[i] = msg[pos + i];
		}

		BulletStruct* bullet = reinterpret_cast<BulletStruct*>(buffer);
		bullets.push_back(bullet);
	}

	switch (msg[1]) {
	case GREEN_BULLETS:
		setGreenBullets(bullets);
		break;
	case BLUE_BULLETS:
		setBlueBullets(bullets);
		break;
	}
}



void CSerializer::translateGameStateMsg(std::vector<char> msg, char &gameState, char & advancedGameState)
{
	gameState = msg[1];
	advancedGameState = msg[2];
}



void CSerializer::setBattlefield(BattlefieldStruct* battlefield)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_battlefield.width = battlefield->width;
	m_battlefield.height = battlefield->height;
}



void CSerializer::setGreenSoldier(SoldierStruct* soldier)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_greenSoldier.center = soldier->center;
	m_greenSoldier.health = soldier->health;
	m_greenSoldier.radius = soldier->radius;
}



void CSerializer::setBlueSoldier(SoldierStruct* soldier)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_blueSoldier.center = soldier->center;
	m_blueSoldier.health = soldier->health;
	m_blueSoldier.radius = soldier->radius;
}



void CSerializer::setGreenBullets(std::vector<BulletStruct*> bullets)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_greenBullets.clear();
	for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
		BulletStruct newBullet;
		newBullet.center = (*bullet)->center;
		newBullet.radius = (*bullet)->radius;
		m_greenBullets.push_back(newBullet);
	}
}



void CSerializer::setBlueBullets(std::vector<BulletStruct*> bullets)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_blueBullets.clear();
	for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
		BulletStruct newBullet;
		newBullet.center = (*bullet)->center;
		newBullet.radius = (*bullet)->radius;
		m_blueBullets.push_back(newBullet);
	}
}



BattlefieldStruct* CSerializer::getBattlefieldStruct()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	BattlefieldStruct* newBttlfldStr = new BattlefieldStruct();
	newBttlfldStr->width = m_battlefield.width;
	newBttlfldStr->height = m_battlefield.height;

	return newBttlfldStr;
}



SoldierStruct* CSerializer::getGreenSoldierStruct()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	SoldierStruct* newGreenSldrdStr = new SoldierStruct();
	newGreenSldrdStr->center = m_greenSoldier.center;
	newGreenSldrdStr->health = m_greenSoldier.health;
	newGreenSldrdStr->radius = m_greenSoldier.radius;

	return newGreenSldrdStr;
}



SoldierStruct* CSerializer::getBlueSoldierStruct()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	SoldierStruct* newBlueSldrdStr = new SoldierStruct();
	newBlueSldrdStr->center = m_blueSoldier.center;
	newBlueSldrdStr->health = m_blueSoldier.health;
	newBlueSldrdStr->radius = m_blueSoldier.radius;

	return newBlueSldrdStr;
}



std::vector<BulletStruct*> CSerializer::getGreenBulletsCopy()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	std::vector<BulletStruct*> greenBulletsCopy;
	for (auto bullet = m_greenBullets.begin(); bullet != m_greenBullets.end(); bullet++) {
		BulletStruct* tmpBullet = new BulletStruct();
		tmpBullet->center = (*bullet).center;
		tmpBullet->radius = (*bullet).radius;
		greenBulletsCopy.push_back(tmpBullet);
	}

	return greenBulletsCopy;
}



std::vector<BulletStruct*> CSerializer::getBlueBulletsCopy()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	std::vector<BulletStruct*> blueBulletsCopy;
	for (auto bullet = m_blueBullets.begin(); bullet != m_blueBullets.end(); bullet++) {
		BulletStruct* tmpBullet = new BulletStruct();
		tmpBullet->center = (*bullet).center;
		tmpBullet->radius = (*bullet).radius;
		blueBulletsCopy.push_back(tmpBullet);
	}

	return blueBulletsCopy;
}



CMoveMsg* CSerializer::createMoveMsg(char pressedKey)
{
	CMoveMsg* moveMsg = new CMoveMsg();
	moveMsg->create(pressedKey);
	return moveMsg;
}



CMoveAndFireMsg* CSerializer::createMoveAndFireMsg(char pressedKey, int mouseX, int mouseY)
{
	CMoveAndFireMsg* moveAndFireMsg = new CMoveAndFireMsg();
	moveAndFireMsg->create(pressedKey, mouseX, mouseY);
	return moveAndFireMsg;
}
