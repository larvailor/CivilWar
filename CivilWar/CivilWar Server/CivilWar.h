#pragma once

#include "ModelsAsDataTypes.h"

#include "Soldier.h"
#include "Bullet.h"

#include <list>
#include <vector>

class CivilWar
{
public:
	CivilWar();
	~CivilWar();

	void initAll();
	void start();

	BattlefieldStruct* getBattlefield() const { return m_battlefield; }
	Soldier* getGreenSoldier() const { return m_greenSoldier; }
	Soldier* getBlueSoldier() const { return m_blueSoldier; }
	std::list<Bullet> getGreenBullets() const { return m_greenBullets; }
	std::list<Bullet> getBlueBullets() const { return m_blueBullets; }

	void translateAndProcessGreenPlayerMsg(std::vector<char> msg);
	void translateAndProcessBluePlayerMsg(std::vector<char> msg);

	bool isRunning() const { return m_isRunning; }

private:
	// variables
	BattlefieldStruct* m_battlefield;

	Soldier* m_greenSoldier;
	Soldier* m_blueSoldier;

	std::list<Bullet> m_greenBullets;
	std::list<Bullet> m_blueBullets;

	bool m_isRunning;

	// methods
	void initBattlefield();
	void initGreenSoldier();
	void initBlueSoldier();

	void handleGreenMoveAndFireMsg(std::vector<char> msg);

	void handleSoldierMove(Soldier* soldier, char pressedKey);
};
