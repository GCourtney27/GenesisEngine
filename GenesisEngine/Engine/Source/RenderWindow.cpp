#include "WindowContainer.h"

#define MAX_LOADSTRING 100

bool RenderWindow::Initialize(WindowContainer * pWindowContainer, HINSTANCE hInstance, int cmdShow, std::string windowTitle, std::string windowClass, int windowWidth, int windowHeight)
{
	this->m_hInstance = hInstance;
	this->m_windowWidth = windowWidth;
	this->m_windowHeight = windowHeight;
	this->m_windowTitle = windowTitle;
	this->m_WindowTitle_Wide = StringHelper::StringToWide(this->m_windowTitle);
	this->m_windowClass = windowClass;
	this->m_windowClass_Wide = StringHelper::StringToWide(this->m_windowClass);

	this->RegisterWindowClass();

	// Create window instance
	m_windowHandle = CreateWindowW(m_windowClass_Wide.c_str(), m_WindowTitle_Wide.c_str(), WS_OVERLAPPEDWINDOW,
									CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!m_windowHandle)
		return false;

	m_hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ENGINE));

	ShowWindow(m_windowHandle, cmdShow);
	UpdateWindow(m_windowHandle);

	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// All other messages
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:
	{
		// Retrieve ptr to window class
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// Foreward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(this->m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr)
		{
			MessageBoxW(NULL, L"Critical Error: Pointer to window container is null durring WM_NCCREATE.", L"Error!", MB_OK);
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
}

bool RenderWindow::ProcessMessages()
{
	// Handle Windows messages
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // Initialize the message structure

	while (PeekMessage(&msg, this->m_windowHandle, 0, 0, PM_REMOVE))
	{
		if (!TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//while (PeekMessage(&msg,  // Where to store message (ifone exists)
	//	this->m_windowHandle, //Handle to window we are checking messages for
	//	0, // Minimum Filter Msg Value - We are not filterinf for specific messages but min and max could be used to do so
	//	0, // Maximum Filter Msg Value
	//	PM_REMOVE)) // Remove mesage after captureing it via PeekMessage
	//{
	//	TranslateMessage(&msg);  // Translate message from virtual key message into character messages
	//	DispatchMessage(&msg); // Dispatch message to our Window Proc for this window
	//}

	// Check if the window was closed
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(this->m_windowHandle))
		{
			this->m_windowHandle = NULL; // Message proccessing loop takes care of destroying this window
			UnregisterClass(m_windowClass.c_str(), this->m_hInstance);
			return false;
		}
	}
	//assert(_CrtCheckMemory()); // Makse sure the heap isn's corrupted on exit
	return true;
}

RenderWindow::~RenderWindow()
{
	if (this->m_windowHandle != NULL)
	{
		UnregisterClass(this->m_windowClass.c_str(), this->m_hInstance);
		DestroyWindow(m_windowHandle);
	}
}

ATOM RenderWindow::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->m_hInstance;
	wcex.hIcon = LoadIcon(this->m_hInstance, MAKEINTRESOURCE(IDI_ENGINE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ENGINE);
	wcex.lpszClassName = m_windowClass_Wide.c_str();
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

