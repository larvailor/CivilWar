#pragma once

#include "CModelsAsDataTypes.h"

#include <Windows.h>
#include <vector>

class Painter {
public:
	Painter();
	~Painter();

	void drawCivilWar(HWND hwnd, SoldierStruct* greenSoldier, SoldierStruct* blueSoldier, std::vector<BulletStruct*> greenBullets, std::vector<BulletStruct*> blueBullets);

private:
	// variables
	HBRUSH m_greenBrush;
	HBRUSH m_blueBrush;



	// methods
	void drawCircle(HWND hwnd, HDC hdc, float x, float y, float radius, HBRUSH hBrush);
};
