#pragma once

#ifndef  UNICODE
#define  UNICODE
#endif 

#include "BaseWindow.h"

#include <Windows.h>

class CWindow : public BaseWindow<CWindow>
{
public:
	CWindow();
	~CWindow();

	PCWSTR  ClassName() const { return L"CivilWar"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
