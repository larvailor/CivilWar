#include "CivilWar.h"

#include "Config.h"
#include "Types.h"

#include "MsgTypesFromClient.h"

#include "BaseCWServerException.h"

#include <cmath>

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
	moveBullets(m_greenBullets);
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
	moveBullets(m_blueBullets);
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



void CivilWar::moveBullets(std::vector<Bullet*> bullets)
{
	// TODO: bullets autside battlefield hould be deleted
	int res = 0;
	for (int i = 0; i < bullets.size(); i++) {
		// process X
		res = bullets[i]->getX();
		switch (bullets[i]->getDirectionX()) {
		case LEFT:
			res = bullets[i]->getX() - bullets[i]->getSpeedX();
			if (res > 0) {
				bullets[i]->setX(res);
			}
			break;
		case RIGHT:
			res = bullets[i]->getX() + bullets[i]->getSpeedX();
			if (res < m_battlefield->width) {
				bullets[i]->setX(res);
			}
			break;
		case NONE_X:
			break;
		}

		// process Y
		res = bullets[i]->getY();
		switch (bullets[i]->getDirectionY()) {
		case UP:
			res = bullets[i]->getY() - bullets[i]->getSpeedY();
			if (res > 0) {
				bullets[i]->setY(res);
			}
			break;
		case DOWN:
			res = bullets[i]->getY() + bullets[i]->getSpeedY();
			if (res < m_battlefield->height) {
				bullets[i]->setY(res);
			}
			break;
		case NONE_X:
			break;
		}
	}
}



void CivilWar::addBullet(Soldier* soldier, std::vector<Bullet*> bullets, std::vector<char> msg)
{
	Point center;
	Radius radius = BULLET_RADIUS;
	DirectionX dirX;
	DirectionY dirY;
	Speed speedX;
	Speed speedY;

	center.x = strToInt(msg[2], msg[3], msg[4], msg[5]);
	center.y = strToInt(msg[6], msg[7], msg[8], msg[9]);

	int cathetX = center.x - soldier->getX();
	if (cathetX < 0) {
		dirX = LEFT;
	}
	else {
		dirX = RIGHT;
	}
	cathetX = abs(cathetX);

	int cathetY = center.y - soldier->getY();
	if (cathetY < 0) {
		dirY = UP;
	}
	else {
		dirY = DOWN;
	}
	cathetY = abs(cathetY);

	int hypotenuse = static_cast<int>(sqrt(cathetX * cathetX + cathetY * cathetY));

	speedX = static_cast<int>(BULLET_SPEED * cathetX / hypotenuse);
	speedY = static_cast<int>(BULLET_SPEED * cathetY / hypotenuse);

	Bullet* bullet = new Bullet(center, radius, dirX, dirY, speedX, speedY);
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
