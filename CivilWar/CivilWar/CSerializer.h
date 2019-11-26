#pragma once

#include "CModelsAsDataTypes.h"

#include "CMoveMsg.h"
#include "CMoveAndFireMsg.h"

#include <vector>
#include <mutex>

class CSerializer
{
public:
	CSerializer();
	~CSerializer();

	void translateMsg(std::vector<char> msg);
	void translateGameStateMsg(std::vector<char> msg, char& gameState, char& advancedGameState);

	void setBattlefield(BattlefieldStruct* battlefield);
	void setGreenSoldier(SoldierStruct* soldier);
	void setBlueSoldier(SoldierStruct* soldier);
	void setGreenBullets(std::vector<BulletStruct*> bullets);
	void setBlueBullets(std::vector<BulletStruct*> bullets);

	BattlefieldStruct* getBattlefieldStruct();
	SoldierStruct* getGreenSoldierStruct();
	SoldierStruct* getBlueSoldierStruct();
	std::vector<BulletStruct*> getGreenBulletsCopy();
	std::vector<BulletStruct*> getBlueBulletsCopy();

	CMoveMsg* createMoveMsg(char pressedKey);
	CMoveAndFireMsg* createMoveAndFireMsg(char pressedKey, int mouseX, int mouseY);

private:
	// variables
	BattlefieldStruct m_battlefield;
	SoldierStruct m_greenSoldier;
	SoldierStruct m_blueSoldier;
	std::vector<BulletStruct> m_greenBullets;
	std::vector<BulletStruct> m_blueBullets;

	std::mutex m_mutex;


	// methods
	void translateBattlefieldMsg(std::vector<char> msg);
	void translateSoldierMsg(std::vector<char> msg);
	void translateBulletsMsg(std::vector<char> msg);
};
