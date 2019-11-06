#include "CivilWar.h"

#include "Config.h"
#include "Types.h"

#include "BaseCWServerException.h"

CivilWar::CivilWar()
	: m_blueSoldier(nullptr),
	m_greenSoldier(nullptr),
	m_is_running(false)
{

}



CivilWar::~CivilWar()
{
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
	m_battlefield.width = BATTLEFIELD_WIDTH;
	m_battlefield.height = BATTLEFIELD_HEIGHT;
}



void CivilWar::initGreenSoldier()
{
	// center
	Point greenSoldierCenter;
	greenSoldierCenter.x = GREEN_SOLDIER_START_X;
	greenSoldierCenter.y = GREEN_SOLDIER_START_Y;
	m_greenSoldier = new Soldier(greenSoldierCenter, GREEN_SOLDIER_RADIUS, GREEN_SOLDIER_HEALTH);
}



void CivilWar::initBlueSoldier()
{
	// center
	Point blueSoldierCenter;
	blueSoldierCenter.x = BLUE_SOLDIER_START_X;
	blueSoldierCenter.y = BLUE_SOLDIER_START_Y;
	m_blueSoldier = new Soldier(blueSoldierCenter, BLUE_SOLDIER_RADIUS, BLUE_SOLDIER_HEALTH);
}



void CivilWar::start()
{
	m_is_running = true;
	
}
