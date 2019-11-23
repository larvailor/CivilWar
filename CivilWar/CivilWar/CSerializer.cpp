#include "CSerializer.h"

#include "CMsgTypesFromServer.h"

CSerializer::CSerializer()
= default;



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

	delete(battlefield);
	delete[](buffer);
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

	delete(soldier);
	delete[](buffer);
}



void CSerializer::translateBulletsMsg(std::vector<char> msg)
{
	// TBD
}



void CSerializer::setBattlefield(BattlefieldStruct* battlefield)
{
	m_battlefield.width = battlefield->width;
	m_battlefield.height = battlefield->height;
}



void CSerializer::setGreenSoldier(SoldierStruct* soldier)
{
	m_greenSoldier.center = soldier->center;
	m_greenSoldier.health = soldier->health;
	m_greenSoldier.radius = soldier->radius;
}



void CSerializer::setBlueSoldier(SoldierStruct* soldier)
{
	m_blueSoldier.center = soldier->center;
	m_blueSoldier.health = soldier->health;
	m_blueSoldier.radius = soldier->radius;
}
