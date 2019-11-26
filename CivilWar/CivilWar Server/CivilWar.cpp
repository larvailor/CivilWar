#include "CivilWar.h"

#include "Config.h"
#include "Types.h"

#include "MsgTypesFromClient.h"

#include "BaseCWServerException.h"

#include <cmath>
#include <mutex>
#include <iostream>

CivilWar::CivilWar() :
	m_battlefield(nullptr),
	m_blueSoldier(nullptr),
	m_greenSoldier(nullptr),
	m_isRunning(false)
{

}



CivilWar::~CivilWar()
{
	m_blltsMvThr->join();

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
	m_blltsMvThr = new std::thread(&CivilWar::moveBulletsThread, this);
}



void CivilWar::translateAndProcessGreenPlayerMsg(std::vector<char> msg)
{
	switch (msg[0]) {
	case MOVE_MSG:
		handleGreenMoveMsg(msg);
		break;
	case MOVE_AND_FIRE_MSG:
		handleGreenMoveAndFireMsg(msg);
		break;
	case DISCONNECT_MSG:
		m_isRunning = false;
		break;
	}
}



void CivilWar::translateAndProcessBluePlayerMsg(std::vector<char> msg)
{
	switch (msg[0]) {
	case MOVE_MSG:
		handleBlueMoveMsg(msg);
		break;
	case MOVE_AND_FIRE_MSG:
		handleBlueMoveAndFireMsg(msg);
		break;
	case DISCONNECT_MSG:
		m_isRunning = false;
		break;
	}
}



void CivilWar::handleGreenMoveMsg(std::vector<char> msg)
{
	moveSoldier(m_greenSoldier, msg[1]);
}



void CivilWar::handleGreenMoveAndFireMsg(std::vector<char> msg)
{
	moveSoldier(m_greenSoldier, msg[1]);
	addBullet(m_greenSoldier, m_greenBullets, msg);
}



void CivilWar::handleBlueMoveMsg(std::vector<char> msg)
{
	moveSoldier(m_blueSoldier, msg[1]);
}



void CivilWar::handleBlueMoveAndFireMsg(std::vector<char> msg)
{
	moveSoldier(m_blueSoldier, msg[1]);
	addBullet(m_blueSoldier, m_blueBullets, msg);
}



void CivilWar::moveSoldier(Soldier* soldier, char pressedKey)
{
	float res;
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



void CivilWar::moveBulletsThread()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	while (m_isRunning) {
		moveBullets(m_greenBullets);
		moveBullets(m_blueBullets);
	}
}



void CivilWar::moveBullets(std::vector<Bullet*> &bullets)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->move();
		if (bullets[i]->getX() < 0 || bullets[i]->getX() > m_battlefield->width || bullets[i]->getY() < 0 || bullets[i]->getY() > m_battlefield->height) {
			bullets.erase(bullets.begin() + i);
		}
	}
}



void CivilWar::addBullet(Soldier* soldier, std::vector<Bullet*>& bullets, std::vector<char> msg)
{
	Point center = soldier->getCenter();
	Radius radius = BULLET_RADIUS;
	DirectionX dirX;
	DirectionY dirY;
	Speed speedX;
	Speed speedY;

	float mouseX = static_cast<float>(strToInt(msg[2], msg[3], msg[4], msg[5]));
	float mouseY = static_cast<float>(strToInt(msg[6], msg[7], msg[8], msg[9]));

	float cathetX = mouseX - soldier->getX();
	if (cathetX < 0) {
		dirX = LEFT;
	}
	else {
		dirX = RIGHT;
	}
	cathetX = abs(cathetX);

	float cathetY = mouseY - soldier->getY();
	if (cathetY < 0) {
		dirY = UP;
	}
	else {
		dirY = DOWN;
	}
	cathetY = abs(cathetY);

	float hypotenuse = static_cast<float>(sqrt(cathetX * cathetX + cathetY * cathetY));

	speedX = static_cast<float>(BULLET_SPEED * (cathetX / hypotenuse));
	speedY = static_cast<float>(BULLET_SPEED * (cathetY / hypotenuse));

	Bullet* bullet = new Bullet(center, radius, dirX, dirY, speedX, speedY);

	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	bullets.push_back(bullet);
}



int CivilWar::strToInt(char thousands, char hundreds, char tens, char units)
{
	int res = static_cast<int>(thousands) * 1000;
	res += static_cast<int>(hundreds) * 100;
	res += static_cast<int>(tens) * 10;
	res += static_cast<int>(units);
	return res;
}
