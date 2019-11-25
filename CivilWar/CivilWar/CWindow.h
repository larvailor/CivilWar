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
		m_serializer(serializer)
	{
		m_painter = new Painter();
	}

	~CWindow();

	PCWSTR  ClassName() const { return L"CivilWar"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	// variales
	Painter* m_painter;
	CSerializer* m_serializer;


	// methods
	void draw();
};
