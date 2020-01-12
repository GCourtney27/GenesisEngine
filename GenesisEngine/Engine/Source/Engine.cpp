#include "Engine.h"

// Systems
#include "..\Source\Graphics\Graphics.h"

#define DELETEPTR(ptr) delete ptr;\
						ptr = 0;

Engine::~Engine()
{
	//DELETEPTR(m_Graphics)
	
}

bool Engine::Initialize(HINSTANCE hInstance, int cmdShow, std::string windowTitle, std::string windowClass, int windowWidth, int windowHeight)
{
	this->m_windowHeight = windowHeight;
	this->m_windowWidth = windowWidth;
	m_Graphics = new Graphics();

	if (!this->m_renderWindow.Initialize(this, hInstance, cmdShow, windowTitle, windowClass, windowWidth, windowHeight))
	{
		MessageBoxW(NULL, L"Failed to initialize render window. Exiting.", L"Error!", MB_OK);
		return false;
	}

	if (!m_Graphics->Initialize(m_renderWindow.GetHWND(), m_windowWidth, m_windowHeight))
	{
		MessageBoxW(NULL, L"Failed to initialize graphics render. Exiting.", L"Error!", MB_OK);
		return false;
	}

	return true;
}

void Engine::Update()
{

}

void Engine::RenderFrame()
{
	m_Graphics->RenderFrame();
}

bool Engine::ProcessMessages()
{
	return this->m_renderWindow.ProcessMessages();
}

void Engine::Shutdown()
{

}

bool Engine::InitGraphics(HWND hwnd)
{
	if (!m_Graphics->Initialize(hwnd, m_windowWidth, m_windowHeight))
	{
		MessageBoxW(NULL, L"Failed to initialize Graphics. Exiting.", L"Fatal Error!", MB_OK);
		return false;
	}
	return true;
}
