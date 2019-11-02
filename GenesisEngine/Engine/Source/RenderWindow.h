#pragma once

#include "Error.h"
#include <string>

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer * pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int windowWidth, int windowHeight);
	bool ProcessMessages();
	HWND GetHWND() const { return this->m_windowHandle; }
	~RenderWindow();

private:
	void RegisterWindowClass();
	HWND m_windowHandle = NULL;
	HINSTANCE m_hInstance = NULL;

	std::string m_windowTitle = "";
	std::wstring m_WindowTitle_Wide = L"";
	std::string m_windowClass = "";
	std::wstring m_windowClass_Wide = L"";

	int m_windowWidth = 0;
	int m_windowHeight = 0;
};