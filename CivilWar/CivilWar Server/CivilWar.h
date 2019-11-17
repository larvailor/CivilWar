#pragma once

#include "ModelsAsDataTypes.h"

#include "Soldier.h"
#include "Bullet.h"

#include <list>

class CivilWar
{
public:
	CivilWar();
	~CivilWar();

	void initAll();
	void start();

	struct battlefield getBattlefield() const { return m_battlefield; }
	Soldier* getGreenSoldier() const { return m_greenSoldier; }
	Soldier* getBlueSoldier() const { return m_blueSoldier; }
	std::list<Bullet> getGreenBullets() const { return m_greenBullets; }
	std::list<Bullet> getBlueBullets() const { return m_blueBullets; }

	bool isRunning() const { return m_is_running; }

private:
	// variables
	struct battlefield m_battlefield;

	Soldier* m_greenSoldier;
	Soldier* m_blueSoldier;

	std::list<Bullet> m_greenBullets;
	std::list<Bullet> m_blueBullets;

	bool m_is_running;

	// methods
	void initBattlefield();
	void initGreenSoldier();
	void initBlueSoldier();
};
