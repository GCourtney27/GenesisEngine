#include "Error.h"

void Error::Log(HRESULT hr, std::string message)
{
	_com_error error(hr);
	//std::wstring errorMessage = L"Error: " + StringHelper::StringToWide(message) + L"\n" + error.ErrorMessage();;
	//MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}

void Error::Log(HRESULT hr, std::wstring message)
{
	_com_error error(hr);
	//std::wstring errorMessage = L"Error: " + message + L"\n" + error.ErrorMessage();;
	//MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}

void Error::Log(COMException& exception)
{
	std::wstring errorMessage = exception.what();
	MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}
