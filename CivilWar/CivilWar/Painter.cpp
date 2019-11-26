#include "Painter.h"

Painter::Painter()
{
	m_greenBrush = CreateSolidBrush(RGB(63, 145, 109));
	m_blueBrush = CreateSolidBrush(RGB(3, 69, 252));
}



Painter::~Painter()
= default;



void Painter::drawCivilWar(HWND hwnd, SoldierStruct* greenSoldier, SoldierStruct* blueSoldier, std::vector<BulletStruct*> greenBullets, std::vector<BulletStruct*> blueBullets)
{
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);

	// green soldier
	drawCircle(hwnd, hdc, greenSoldier->center.x, greenSoldier->center.y, greenSoldier->radius, m_greenBrush);
	delete(greenSoldier);

	// blue soldier
	drawCircle(hwnd, hdc, blueSoldier->center.x, blueSoldier->center.y, blueSoldier->radius, m_blueBrush);
	delete(blueSoldier);

	// green bullets
	for (auto bullet = greenBullets.begin(); bullet != greenBullets.end(); bullet++) {
		drawCircle(hwnd, hdc, (*bullet)->center.x, (*bullet)->center.y, (*bullet)->radius, m_greenBrush);
	}

	// blue bullets
	for (auto bullet = blueBullets.begin(); bullet != blueBullets.end(); bullet++) {
		drawCircle(hwnd, hdc, (*bullet)->center.x, (*bullet)->center.y, (*bullet)->radius, m_blueBrush);
	}

	EndPaint(hwnd, &ps);
}



void Painter::drawCircle(HWND hwnd, HDC hdc, float x, float y, float radius, HBRUSH hBrush)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

	SelectObject(hdc, hOld);
}
