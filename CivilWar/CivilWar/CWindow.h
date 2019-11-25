#pragma once

#ifndef  UNICODE
#define  UNICODE
#endif 

#include "BaseWindow.h"
#include "Painter.h"
#include "CSerializer.h"

#include <Windows.h>

class CWindow : public BaseWindow<CWindow>
{
public:
	CWindow(CSerializer* serializer, HINSTANCE hInstance, int nCmdShow) :
		BaseWindow(hInstance, nCmdShow),
		m_serializer(serializer),
		m_pressedKey(NULL),
		m_cursor({ -1 })
	{
		m_painter = new Painter();
	}

	~CWindow();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	PCWSTR  ClassName() const { return L"CivilWar"; }
	char getPressedKey() const { return m_pressedKey; }
	int getCursorX() const { return m_cursor.x; }
	int getCursorY() const { return m_cursor.y; }

	void dropPressedKey() { m_pressedKey = NULL; }
	void dropCursor() { m_cursor = { -1 }; }

private:
	// variales
	Painter* m_painter;
	CSerializer* m_serializer;
	char m_pressedKey;
	POINT m_cursor;

	// methods
	void draw();
};
