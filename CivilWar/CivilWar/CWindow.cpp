#include "CWindow.h"

#include "BaseCWException.h"

CWindow::~CWindow()
= default;



LRESULT CWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
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
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}



void CWindow::draw()
{
	m_painter->drawSoldiers(m_hwnd, m_serializer->getGreenSoldierStruct(), m_serializer->getBlueSoldierStruct());
	// TODO: draw bullets
}
