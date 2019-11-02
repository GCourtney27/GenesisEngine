#include "Renderer.h"

bool Renderer::Initialize(HWND hwnd, int windowWidth, int windowHeight)
{
	this->m_windowWidth = windowWidth;
	this->m_windowHeight = windowHeight;

	if (!IniitalizeDirect3D_11(hwnd))
		return false;


	return true;
}

bool Renderer::IniitalizeDirect3D_11(HWND hwnd)
{
	// -- Obtain D3D11 compatible adapter -- //
	std::vector<AdapterData> adapters = AdapterReader::GetGraphicsAdapters();
	if (adapters.size() < 1)
	{
		MessageBoxW(NULL, L"Failed to get Direct3D compatable adapter. Does your video card support DirectX 11?", L"Fatal Error", MB_ICONEXCLAMATION);
		return false;
	}

	// -- Initialize Swap Chain -- //
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferDesc.Width = m_windowWidth;
	scd.BufferDesc.Height = m_windowHeight;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator= 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;



	return true;
}
