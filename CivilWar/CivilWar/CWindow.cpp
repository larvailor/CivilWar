#include "CWindow.h"

#include "BaseCWException.h"

CWindow::~CWindow()
= default;



LRESULT CWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		SetTimer(m_hwnd, 1, 1000, NULL);
		return 0;
	case WM_TIMER:
		GetCursorPos(&m_cursor);
		return 0;
	case WM_PAINT:
		draw();
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case 'W':
			m_pressedKey = 'W';
			break;
		case 'A':
			m_pressedKey = 'A';
			break;
		case 'S':
			m_pressedKey = 'S';
			break;
		case 'D':
			m_pressedKey = 'D';
			break;
		}
		return 0;
	case WM_DESTROY:
		KillTimer(m_hwnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}



void CWindow::draw()
{
	m_painter->drawCivilWar(
		m_hwnd,
		m_serializer->getGreenSoldierStruct(),
		m_serializer->getBlueSoldierStruct(),
		m_serializer->getGreenBulletsCopy(),
		m_serializer->getBlueBulletsCopy()
	);
}
