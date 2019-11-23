#pragma once

#include "Types.h"
#include "ModelsAsDataTypes.h"

#include "Soldier.h"
#include "Bullet.h"

#include "BattlefieldMsg.h"
#include "SoldierMsg.h"

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

	void setBattlefield(BattlefieldStruct* bttlfieldStr);
	void setGreenSoldier(Soldier* greenSoldier);
	void setBlueSoldier(Soldier* blueSoldier);

private:
	// variables
	BattlefieldStruct m_battlefield;
	SoldierStruct m_greenSoldier;
	SoldierStruct m_blueSoldier;

	std::list<BulletStruct> m_bullets;
};