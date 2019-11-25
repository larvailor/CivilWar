#pragma once

#include "CModelsAsDataTypes.h"

#include "CMoveAndFireMsg.h"

#include <vector>

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

	BattlefieldStruct* getBattlefieldStruct();
	SoldierStruct* getGreenSoldierStruct();
	SoldierStruct* getBlueSoldierStruct();

	CMoveAndFireMsg* createMoveAndFireMsg(char pressedKey, int mouseX, int mouseY);

private:
	// variables
	BattlefieldStruct m_battlefield;
	SoldierStruct m_greenSoldier;
	SoldierStruct m_blueSoldier;



	// methods
	void translateBattlefieldMsg(std::vector<char> msg);
	void translateSoldierMsg(std::vector<char> msg);
	void translateBulletsMsg(std::vector<char> msg);
};
