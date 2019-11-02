#include "Engine.h"
#include "Graphics/Renderer.h"


Engine::~Engine()
{
}

bool Engine::Initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int windowWidth, int windowHeight)
{
	this->m_windowHeight = windowHeight;
	this->m_windowWidth = windowWidth;

	MessageBoxW(NULL, L"Hello from Genesis Engine!", L"Greetings!", MB_OKCANCEL);

	return true;
}

void Engine::Shutdown()
{

}