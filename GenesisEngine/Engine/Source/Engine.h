#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#pragma once
#include "WindowContainer.h"

class ENGINE_API Engine
{
public:
	Engine() {}
	~Engine();

	bool Initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int windowWidth, int windowHeight);

	void Shutdown();
private:
	int m_windowWidth = 0;
	int m_windowHeight = 0;
};

