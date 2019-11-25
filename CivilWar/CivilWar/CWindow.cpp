#include "CWindow.h"

#include "BaseCWException.h"

CWindow::~CWindow()
= default;



LRESULT CWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
