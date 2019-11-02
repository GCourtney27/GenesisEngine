#pragma once
#include "RenderWindow.h"

class WindowContainer
{
public:
	WindowContainer();

	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	RenderWindow m_renderWindow;

};