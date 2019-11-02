#pragma once
#include "..\Engine.h"
#include "AdapterReader.h"

#pragma comment(lib, "d3d11.lib")

class Renderer
{
public:
	bool Initialize(HWND hwnd, int windowWidth, int windowHeight);
	bool IniitalizeDirect3D_11(HWND hwnd);

private:
	int m_windowWidth = 0;
	int m_windowHeight = 0;
};