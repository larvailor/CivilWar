#pragma once

#include "Types.h"
#include "ModelsAsDataTypes.h"

#include "Soldier.h"
#include "Bullet.h"

#include "SoldierMsg.h"

#include <list>

class Serializer
{
public:
	Serializer();
	~Serializer();



	// methods
	void init(struct battlefield bttlfieldStr, Soldier* greenSoldierClass, Soldier* blueSoldierClass);
	SoldierMsg* createGreenSoldierMsg(Soldier* greenSoldier);
	SoldierMsg* createBlueSoldierMsg(Soldier* blueSoldier);

	void setBattlefield(struct battlefield bttlfieldStr);
	void setGreenSoldier(Soldier* greenSoldier);
	void setBlueSoldier(Soldier* blueSoldier);

private:
	// variables
	struct battlefield m_battlefield;

	struct soldier m_greenSoldier;
	struct soldier m_blueSoldier;

	std::list<struct bullet> m_bullets;
};