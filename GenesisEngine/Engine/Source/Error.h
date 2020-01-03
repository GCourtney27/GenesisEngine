#pragma once
#include "COMException.h"
#include <Windows.h>

class Error
{
public:
	static void Log(HRESULT hr, std::string message);
	static void Log(HRESULT hr, std::wstring message);
	static void Log(COMException & exception);
};