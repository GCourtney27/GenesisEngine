#include "..\EngineExport.h"

#pragma once
#include "WindowContainer.h"
#include <string>

class Graphics;

class ENGINE_API Engine : WindowContainer
{
public:
	Engine() {}
	~Engine();

	bool Initialize(HINSTANCE hInstance, int cmdShow, std::string windowTitle, std::string windowClass, int windowWidth, int windowHeight);
	bool ProcessMessages();
	void Update();
	void RenderFrame();
	void Shutdown();

	// DEBUG
	bool InitGraphics(HWND hwnd);

private:
	Graphics* m_Graphics = nullptr;

	int m_windowWidth = 0;
	int m_windowHeight = 0;
};

