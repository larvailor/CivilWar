#include "Painter.h"

Painter::Painter()
{
	m_greenBrush = CreateSolidBrush(RGB(63, 145, 109));
	m_blueBrush = CreateSolidBrush(RGB(3, 69, 252));
}



Painter::~Painter()
= default;



void Painter::drawSoldiers(HWND hWnd, SoldierStruct* greenSoldier, SoldierStruct* blueSoldier)
{
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);

	// green soldier
	drawCircle(hWnd, hdc, greenSoldier->center.x, greenSoldier->center.y, greenSoldier->radius, m_greenBrush);
	delete(greenSoldier);

	// blue soldier
	drawCircle(hWnd, hdc, blueSoldier->center.x, blueSoldier->center.y, blueSoldier->radius, m_blueBrush);
	delete(blueSoldier);

	EndPaint(hWnd, &ps);
}



void Painter::drawCircle(HWND hWnd, HDC hdc, int x, int y, int radius, HBRUSH hBrush)
{
	HBRUSH hOld = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

	SelectObject(hdc, hOld);
}
