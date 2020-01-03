#pragma once

#include "Error.h"
#include <string>
#include "..\..\WindowsAPI\framework.h"
#include "..\..\WindowsAPI\Resource.h"

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer * pWindowContainer, HINSTANCE hInstance, int cmdShow, std::string window_title, std::string window_class, int windowWidth, int windowHeight);
	bool ProcessMessages();
	HWND GetHWND() const { return this->m_windowHandle; }
	HINSTANCE GetWindowInstance() { return this->m_hInstance; }
	~RenderWindow();

private:
	ATOM RegisterWindowClass();
	HWND m_windowHandle = NULL;
	HINSTANCE m_hInstance = NULL;
	HACCEL m_hAccelTable = NULL;

	std::string m_windowTitle = "";
	std::wstring m_WindowTitle_Wide = L"";
	std::string m_windowClass = "";
	std::wstring m_windowClass_Wide = L"";

	int m_windowWidth = 0;
	int m_windowHeight = 0;
};