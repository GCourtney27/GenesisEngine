#include "Renderer.h"
#include "..\Error.h"

bool Renderer::Initialize(HWND hwnd, eGraphicsAPIs targetAPI, int windowWidth, int windowHeight)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	switch (targetAPI)
	{
	case D3D_11:
		m_pActiveAPI = new Direct3D_11();
		m_pActiveAPI->Initialize(hwnd, m_windowWidth, m_windowHeight);
		break;
	case D3D_12:

	default:
		MessageBoxW(NULL, L"Failed to determine appropriet rendering API!", L"Fatal Error", MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

void Renderer::ClearRenderTargetView()
{
	m_pActiveAPI->ClearRenderTargetView();
}

void Renderer::ClearDepthStencilView()
{
	m_pActiveAPI->ClearDepthStencilView();
}

void Renderer::PresentFrame()
{
	m_pActiveAPI->PresentFrame();
}

#pragma region Direct3D 11
bool Direct3D_11::Initialize(HWND hwnd, int windowWidth, int windowHeight)
{
	try
	{
		// -- Obtain D3D11 compatible adapter -- //
		std::vector<AdapterData> adapters = AdapterReader::GetGraphicsAdapters();
		if (adapters.size() < 1)
		{
			MessageBoxW(NULL, L"Failed to get Direct3D compatable adapter. Does your video card support DirectX 11?", L"Error", MB_ICONEXCLAMATION);
			return false;
		}

		// -- Initialize Swap Chain -- //
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		scd.BufferDesc.Width = windowWidth;
		scd.BufferDesc.Height = windowHeight;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
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

		HRESULT hr;
		hr = D3D11CreateDeviceAndSwapChain(adapters[0].pAdapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			NULL,
			NULL,
			NULL,
			0,
			D3D11_SDK_VERSION,
			&scd,
			pSwapChain.GetAddressOf(),
			pDevice.GetAddressOf(),
			NULL,
			pDeviceContext.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create swapchain!");

		hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to set backbuffer SwapChain", L"Error", MB_OK);
			return false;
		}

		hr = pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, pRenderTargetView.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to create render target view for back buffer", L"Error", MB_OK);
			return false;
		}

		// -- Create Depth Stencil View -- //
		CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, windowWidth, windowHeight);
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		pDevice->CreateTexture2D(&depthStencilDesc, NULL, pDepthStencilBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to create depth stencil buffer Texture2D", L"Error", MB_OK);
			return false;
		}
		hr = pDevice->CreateDepthStencilView(pDepthStencilBuffer.Get(), NULL, pDepthStencilView.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to create depth stencil view", L"Error", MB_OK);
			return false;
		}
		pDeviceContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());

		// -- Create Depth Stencil State (Z buffer) -- //
		CD3D11_DEPTH_STENCIL_DESC depthstencildesc(D3D11_DEFAULT);
		depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		hr = pDevice->CreateDepthStencilState(&depthstencildesc, pDepthStencilState.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to create depth stencil state for Z buffer", L"Error", MB_OK);
			return false;
		}

		// -- Create and set viewport -- //
		CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight));
		pDeviceContext->RSSetViewports(1, &viewport);

		// -- Create RasterizerState -- //
		CD3D11_RASTERIZER_DESC rasterizerDesc(D3D11_DEFAULT);
		rasterizerDesc.AntialiasedLineEnable = true;
		rasterizerDesc.MultisampleEnable = true;
		hr = pDevice->CreateRasterizerState(&rasterizerDesc, pRasterizerState.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to create rasterizer state", L"Error", MB_OK);
			return false;
		}

		// -- Create Blend State -- //
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(CD3D11_BLEND_DESC));
		D3D11_RENDER_TARGET_BLEND_DESC rtbd;
		ZeroMemory(&rtbd, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));
		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
		blendDesc.RenderTarget[0] = rtbd;
		hr = pDevice->CreateBlendState(&blendDesc, pBlendState.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to create blend state", L"Error", MB_OK);
			return false;
		}

		CD3D11_SAMPLER_DESC samplerDesc(D3D11_DEFAULT);
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		hr = pDevice->CreateSamplerState(&samplerDesc, pSamplerState.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxW(NULL, L"Failed to create sampler state", L"Error", MB_OK);
			return false;
		}
	}
	catch (COMException & exception)
	{
		Error::Log(exception);
		return false;
	}

	return true;
}

void Direct3D_11::ClearRenderTargetView()
{
	pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), m_clearColor);
}

void Direct3D_11::ClearDepthStencilView()
{
	pDeviceContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Direct3D_11::PresentFrame()
{
	pSwapChain->Present(0, NULL);
}
#pragma endregion 

