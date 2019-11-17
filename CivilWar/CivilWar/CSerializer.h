#pragma once

#include "CModelsAsDataTypes.h"

#include <vector>

class CSerializer
{
public:
	CSerializer();
	~CSerializer();

	void translateMsg(std::vector<char> msg);

	void setBattlefield(BattlefieldStruct* battlefield);
	void setGreenSoldier(SoldierStruct* soldier);
	void setBlueSoldier(SoldierStruct* soldier);

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
