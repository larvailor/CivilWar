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
	case GAME_STATE_MSG_TYPE:
		//translateGameStateMsg(msg);
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
	// TBD
}



void CSerializer::translateGameStateMsg(std::vector<char> msg, char &gameState, char &advancedInfo)
{
	switch (msg[1])	{
	case BEFORE_BATTLE_STATE:
		gameState = BEFORE_BATTLE_STATE;
		break;
	case BATTLE_STATE:
		gameState = BATTLE_STATE;
		break;
	case AFTER_BATTLE_STATE:
		gameState = AFTER_BATTLE_STATE;
		switch (msg[2]) {
		case GREEN_WIN:
			advancedInfo = GREEN_WIN;
			break;
		case BLUE_WIN:
			advancedInfo = BLUE_WIN;
			break;
		}
		break;
	}
}



void CSerializer::setBattlefield(BattlefieldStruct* battlefield)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_battlefield.width = battlefield->width;
	m_battlefield.height = battlefield->height;
}



void CSerializer::setGreenSoldier(SoldierStruct* soldier)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_greenSoldier.center = soldier->center;
	m_greenSoldier.health = soldier->health;
	m_greenSoldier.radius = soldier->radius;
}



void CSerializer::setBlueSoldier(SoldierStruct* soldier)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_blueSoldier.center = soldier->center;
	m_blueSoldier.health = soldier->health;
	m_blueSoldier.radius = soldier->radius;
}



BattlefieldStruct* CSerializer::getBattlefieldStruct()
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	BattlefieldStruct* newBttlfldStr = new BattlefieldStruct();
	newBttlfldStr->width = m_battlefield.width;
	newBttlfldStr->height = m_battlefield.height;

	return newBttlfldStr;
}



SoldierStruct* CSerializer::getGreenSoldierStruct()
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	SoldierStruct* newGreenSldrdStr = new SoldierStruct();
	newGreenSldrdStr->center = m_greenSoldier.center;
	newGreenSldrdStr->health = m_greenSoldier.health;
	newGreenSldrdStr->radius = m_greenSoldier.radius;

	return newGreenSldrdStr;
}



SoldierStruct* CSerializer::getBlueSoldierStruct()
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	SoldierStruct* newBlueSldrdStr = new SoldierStruct();
	newBlueSldrdStr->center = m_greenSoldier.center;
	newBlueSldrdStr->health = m_greenSoldier.health;
	newBlueSldrdStr->radius = m_greenSoldier.radius;

	return newBlueSldrdStr;
}
