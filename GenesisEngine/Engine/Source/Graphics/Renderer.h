#pragma once
#include "AdapterReader.h"
#include "..\Engine.h"
#include <wrl/client.h>

#pragma comment(lib, "d3d11.lib")

class Renderer
{
public:
	Renderer() {}
	bool Initialize(HWND hwnd, int windowWidth, int windowHeight);
	bool IniitalizeDirect3D_11(HWND hwnd);
	void RenderFrame();

private:
	int m_windowWidth = 0;
	int m_windowHeight = 0;

	// D3D Parameters
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	// SwapChian
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	// Depth Stencil
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState;
	// Rasterizer
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState;
	
	Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState;



	
};