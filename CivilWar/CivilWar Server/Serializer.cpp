#include "Serializer.h"

Serializer::Serializer()
= default;



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
	m_battlefield.height = battlefieldStruct->height;
	m_battlefield.width = battlefieldStruct->width;
}



void Serializer::setGreenSoldier(Soldier* greenSoldier)
{
	m_greenSoldier.center = greenSoldier->getCenter();
	m_greenSoldier.radius = greenSoldier->getRadius();
	m_greenSoldier.health = greenSoldier->getHealth();
}



void Serializer::setBlueSoldier(Soldier* blueSoldier)
{
	m_blueSoldier.center = blueSoldier->getCenter();
	m_blueSoldier.radius = blueSoldier->getRadius();
	m_blueSoldier.health = blueSoldier->getHealth();
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
