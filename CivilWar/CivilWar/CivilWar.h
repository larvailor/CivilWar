#pragma once

#include "BaseCWException.h"

#include "Soldier.h"
#include "Bullet.h"

#include <list>

class CivilWar
{
public:
	CivilWar();
	~CivilWar();

	void start(Soldier* greenSoldier, Soldier* blueSoldier);

	Soldier* getGreenSoldier();
	Soldier* getBlueSoldier();

	std::list<Bullet> getGreenBullets();
	std::list<Bullet> getBlueBullets();

private:
	Soldier* m_greenSoldier;
	Soldier* m_blueSoldier;

	std::list<Bullet> m_greenBullets;
	std::list<Bullet> m_blueBullets;
};
