#pragma once

#include "CModelsAsDataTypes.h"

#include <Windows.h>

class Painter {
public:
	Painter();
	~Painter();

	void drawSoldiers(HWND hwnd, SoldierStruct* greenSoldier, SoldierStruct* blueSoldier);

private:
	// variables
	HBRUSH m_greenBrush;
	HBRUSH m_blueBrush;



	// methods
	void drawCircle(HWND hwnd, HDC hdc, int x, int y, int radius, HBRUSH hBrush);
};
