#include "CivilWar.h"

CivilWar::CivilWar()
	: m_blueSoldier(nullptr),
	m_greenSoldier(nullptr)
{

}



CivilWar::~CivilWar()
{
	delete(m_blueSoldier);
	delete(m_greenSoldier);
}



void CivilWar::start(Soldier* greenSoldier, Soldier* blueSoldier)
{
	if (greenSoldier == nullptr) {
		throw(BaseCWException("Green soldier pointer is equal to nullptr"));
	}
	if (blueSoldier == nullptr) {
		throw(BaseCWException("Blue soldier pointer is equal to nullptr"));
	}

	m_greenSoldier = greenSoldier;
	m_blueSoldier = blueSoldier;
}


Soldier* CivilWar::getGreenSoldier()
{
	return m_greenSoldier;
}

Soldier* CivilWar::getBlueSoldier()
{
	return m_blueSoldier;
}

std::list<Bullet> CivilWar::getGreenBullets()
{
	return m_greenBullets;
}

std::list<Bullet> CivilWar::getBlueBullets()
{
	return m_blueBullets;
}
