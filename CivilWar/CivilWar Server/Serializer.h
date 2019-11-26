#pragma once

#include "Types.h"
#include "ModelsAsDataTypes.h"
#include "GameState.h"

#include "Soldier.h"
#include "Bullet.h"

#include "BattlefieldMsg.h"
#include "SoldierMsg.h"
#include "BulletsMsg.h"
#include "GameStateMsg.h"

#include <mutex>
#include <list>

class Serializer
{
public:
	Serializer();
	~Serializer();



	// methods
	void init(BattlefieldStruct* bttlfieldStr, Soldier* greenSoldierClass, Soldier* blueSoldierClass);
	BattlefieldMsg* createBattlefieldMsg(BattlefieldStruct* battlefieldStruct);
	SoldierMsg* createGreenSoldierMsg(Soldier* greenSoldier);
	SoldierMsg* createBlueSoldierMsg(Soldier* blueSoldier);
	BulletsMsg* createGreenBulletsMsg(std::vector<Bullet*> bullets);
	BulletsMsg* createBlueBulletsMsg(std::vector<Bullet*> bullets);
	GameStateMsg* createGameStateMsg(char gameState, char advancedInfo = NULL);

	void setBattlefield(BattlefieldStruct* bttlfieldStr);
	void setGreenSoldier(Soldier* greenSoldier);
	void setBlueSoldier(Soldier* blueSoldier);
	void setGreenBullets(std::vector<Bullet*> greenBullets);
	void setBlueBullets(std::vector<Bullet*> blueBullets);

private:
	// variables
	BattlefieldStruct m_battlefield;
	SoldierStruct m_greenSoldier;
	SoldierStruct m_blueSoldier;

	std::vector<BulletStruct> m_greenBullets;
	std::vector<BulletStruct> m_blueBullets;

	std::mutex m_mutex;
};
