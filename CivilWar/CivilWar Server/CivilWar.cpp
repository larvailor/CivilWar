#include "CivilWar.h"

#include "Config.h"
#include "Types.h"

#include "MsgTypesFromClient.h"

#include "BaseCWServerException.h"

CivilWar::CivilWar() :
	m_battlefield(nullptr),
	m_blueSoldier(nullptr),
	m_greenSoldier(nullptr),
	m_isRunning(false)
{

}



CivilWar::~CivilWar()
{
	delete(m_battlefield);
	delete(m_blueSoldier);
	delete(m_greenSoldier);
}



void CivilWar::initAll()
{
	initBattlefield();
	initGreenSoldier();
	initBlueSoldier();
}



void CivilWar::initBattlefield()
{
	m_battlefield = new BattlefieldStruct();
	m_battlefield->width = BATTLEFIELD_WIDTH;
	m_battlefield->height = BATTLEFIELD_HEIGHT;
}



void CivilWar::initGreenSoldier()
{
	// center
	Point greenSoldierCenter;
	greenSoldierCenter.x = GREEN_SOLDIER_START_X;
	greenSoldierCenter.y = GREEN_SOLDIER_START_Y;
	m_greenSoldier = new Soldier(greenSoldierCenter, GREEN_SOLDIER_RADIUS, GREEN_SOLDIER_HEALTH, GREEN_SOLDIER_SPEED);
}



void CivilWar::initBlueSoldier()
{
	// center
	Point blueSoldierCenter;
	blueSoldierCenter.x = BLUE_SOLDIER_START_X;
	blueSoldierCenter.y = BLUE_SOLDIER_START_Y;
	m_blueSoldier = new Soldier(blueSoldierCenter, BLUE_SOLDIER_RADIUS, BLUE_SOLDIER_HEALTH, BLUE_SOLDIER_SPEED);
}




void CivilWar::start()
{
	m_isRunning = true;
	
}



void CivilWar::translateAndProcessGreenPlayerMsg(std::vector<char> msg)
{
	switch (msg[0]) {
	case MOVE_AND_FIRE_MSG:
		handleGreenMoveAndFireMsg(msg);
		break;
	case DISCONNECT_MSG:
		m_isRunning = false;
		break;
	}
}



void CivilWar::handleGreenMoveAndFireMsg(std::vector<char> msg)
{
	handleSoldierMove(m_greenSoldier, msg[1]);
	//createBullet();
	// TODO: handle fire
}



void CivilWar::translateAndProcessBluePlayerMsg(std::vector<char> msg)
{
	handleSoldierMove(m_blueSoldier, msg[1]);
	// TODO: handle fire
}



void CivilWar::handleSoldierMove(Soldier* soldier, char pressedKey)
{
	int res;
	switch (pressedKey) {
	case 'W':
		res = soldier->getY() - soldier->getSpeed();
		if (res > 0) {
			soldier->setY(res);
		}
		break;
	case 'A':
		res = soldier->getX() - soldier->getSpeed();
		if (res > 0) {
			soldier->setX(res);
		}
		break;
	case 'S':
		res = soldier->getY() + soldier->getSpeed();
		if (res < m_battlefield->height) {
			soldier->setY(res);
		}
		break;
	case 'D':
		res = soldier->getX() + soldier->getSpeed();
		if (res < m_battlefield->width) {
			soldier->setX(res);
		}
		break;
	}
}

