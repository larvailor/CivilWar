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
		m_pressedKey(NULL)
	{
		m_painter = new Painter();
	}

	~CWindow();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	PCWSTR  ClassName() const { return L"CivilWar"; }
	char getPressedKey() const { return m_pressedKey; }
	void dropPressedKey() { m_pressedKey = NULL; }

private:
	// variales
	Painter* m_painter;
	CSerializer* m_serializer;
	char m_pressedKey;

	// methods
	void draw();
};
