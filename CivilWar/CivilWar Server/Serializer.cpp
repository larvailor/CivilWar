#include "Serializer.h"

#include <mutex>

Serializer::Serializer() :
	m_battlefield({ 0 }),
	m_greenSoldier({ 0 }),
	m_blueSoldier({ 0 })
{
}



Serializer::~Serializer()
= default;



void Serializer::init(BattlefieldStruct* battlefieldStruct, Soldier* greenSoldierClass, Soldier* blueSoldierClass)
{
	setBattlefield(battlefieldStruct);
	setGreenSoldier(greenSoldierClass);
	setBlueSoldier(blueSoldierClass);
}



void Serializer::setBattlefield(BattlefieldStruct* battlefieldStruct)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_battlefield.height = battlefieldStruct->height;
	m_battlefield.width = battlefieldStruct->width;
}



void Serializer::setGreenSoldier(Soldier* greenSoldier)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_greenSoldier.center = greenSoldier->getCenter();
	m_greenSoldier.radius = greenSoldier->getRadius();
	m_greenSoldier.health = greenSoldier->getHealth();
}



void Serializer::setBlueSoldier(Soldier* blueSoldier)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_blueSoldier.center = blueSoldier->getCenter();
	m_blueSoldier.radius = blueSoldier->getRadius();
	m_blueSoldier.health = blueSoldier->getHealth();
}



void Serializer::setGreenBullets(std::vector<Bullet*> greenBullets)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_greenBullets.clear();
	for (auto bullet = greenBullets.begin(); bullet != greenBullets.end(); bullet++) {
		BulletStruct newBullet;
		newBullet.center = (*bullet)->getCenter();
		newBullet.radius = (*bullet)->getRadius();
		m_greenBullets.push_back(newBullet);
	}
}



void Serializer::setBlueBullets(std::vector<Bullet*> blueBullets)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	m_blueBullets.clear();
	for (auto bullet = blueBullets.begin(); bullet != blueBullets.end(); bullet++) {
		BulletStruct newBullet;
		newBullet.center = (*bullet)->getCenter();
		newBullet.radius = (*bullet)->getRadius();
		m_blueBullets.push_back(newBullet);
	}
}



BattlefieldMsg* Serializer::createBattlefieldMsg(BattlefieldStruct* battlefieldStruct)
{
	setBattlefield(battlefieldStruct);

	BattlefieldMsg* battlefieldMsg = new BattlefieldMsg();
	battlefieldMsg->create(&m_battlefield);
	return battlefieldMsg;
}



SoldierMsg* Serializer::createGreenSoldierMsg(Soldier* greenSoldier)
{
	setGreenSoldier(greenSoldier);

	SoldierMsg* greenSldrMsg = new SoldierMsg(GREEN_SOLDIER);
	greenSldrMsg->create(&m_greenSoldier);
	return greenSldrMsg;
}



SoldierMsg* Serializer::createBlueSoldierMsg(Soldier* blueSoldier)
{
	setBlueSoldier(blueSoldier);

	SoldierMsg* blueSldrMsg = new SoldierMsg(BLUE_SOLDIER);
	blueSldrMsg->create(&m_blueSoldier);
	return blueSldrMsg;
}



BulletsMsg* Serializer::createGreenBulletsMsg(std::vector<Bullet*> bullets)
{
	setGreenBullets(bullets);

	BulletsMsg* bulletsMsg = new BulletsMsg(m_greenBullets.size(), GREEN_BULLETS);
	bulletsMsg->create(m_greenBullets);
	return bulletsMsg;
}



BulletsMsg* Serializer::createBlueBulletsMsg(std::vector<Bullet*> bullets)
{
	setBlueBullets(bullets);

	BulletsMsg* bulletsMsg = new BulletsMsg(m_blueBullets.size(), GREEN_BULLETS);
	bulletsMsg->create(m_blueBullets);
	return bulletsMsg;
}



GameStateMsg* Serializer::createGameStateMsg(char gameState, char advancedInfo)
{
	GameStateMsg* gameStateMsg = new GameStateMsg(gameState, advancedInfo);
	gameStateMsg->create(nullptr);
	return gameStateMsg;
}
