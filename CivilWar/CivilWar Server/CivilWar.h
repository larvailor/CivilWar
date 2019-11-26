#pragma once

#include "ModelsAsDataTypes.h"

#include "Soldier.h"
#include "Bullet.h"

#include <list>
#include <vector>
#include <thread>

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
	std::vector<Bullet*> getGreenBullets() const { return m_greenBullets; }
	std::vector<Bullet*> getBlueBullets() const { return m_blueBullets; }

	void translateAndProcessGreenPlayerMsg(std::vector<char> msg);
	void translateAndProcessBluePlayerMsg(std::vector<char> msg);

	bool isRunning() const { return m_isRunning; }

private:
	// variables
	BattlefieldStruct* m_battlefield;

	Soldier* m_greenSoldier;
	Soldier* m_blueSoldier;

	std::vector<Bullet*> m_greenBullets;
	std::vector<Bullet*> m_blueBullets;

	bool m_isRunning;

	std::thread* m_blltsMvThr;


	// methods
	void initBattlefield();
	void initGreenSoldier();
	void initBlueSoldier();

	void handleGreenMoveMsg(std::vector<char> msg);
	void handleBlueMoveMsg(std::vector<char> msg);
	void handleGreenMoveAndFireMsg(std::vector<char> msg);
	void handleBlueMoveAndFireMsg(std::vector<char> msg);

	void moveSoldier(Soldier* soldier, char pressedKey);
	void moveBulletsThread();
	void moveBullets(std::vector<Bullet*>& bullets);

	void addBullet(Soldier* soldier, std::vector<Bullet*>& bullets, std::vector<char> msg);

	int strToInt(char thousands, char hundreds, char tens, char units);
};
