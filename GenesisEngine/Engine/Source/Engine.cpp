#include "Engine.h"

// Systems
#include "..\Source\Graphics\Renderer.h"

Engine::~Engine()
{
	//delete m_renderer;
}

bool Engine::Initialize(HINSTANCE hInstance, int cmdShow, std::string windowTitle, std::string windowClass, int windowWidth, int windowHeight)
{
	this->m_windowHeight = windowHeight;
	this->m_windowWidth = windowWidth;
	m_renderer = new Renderer();

	if (!this->m_renderWindow.Initialize(this, hInstance, cmdShow, windowTitle, windowClass, windowWidth, windowHeight))
	{
		MessageBoxW(NULL, L"Failed to initialize renderer window. Exiting.", L"Error!", MB_OK);
		return false;
	}
	HWND e = m_renderWindow.GetHWND();
	if (!m_renderer->Initialize(m_renderWindow.GetHWND(), m_windowWidth, m_windowHeight))
		return false;

	return true;
}

void Engine::Update()
{

}

void Engine::RenderFrame()
{
	m_renderer->RenderFrame();
}

bool Engine::ProcessMessages()
{
	return this->m_renderWindow.ProcessMessages();
}

void Engine::Shutdown()
{

}

bool Engine::InitRenderer(HWND hwnd)
{
	if (!m_renderer->Initialize(hwnd, m_windowWidth, m_windowHeight))
	{
		MessageBoxW(NULL, L"Failed to initialize renderer. Exiting.", L"Fatal Error!", MB_OK);
		return false;
	}
	return true;
}
