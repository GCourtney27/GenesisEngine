#pragma once
#include "AdapterReader.h"
#include <wrl/client.h>

#pragma comment(lib, "d3d11.lib")

class GraphicsAPI
{
public:
	virtual bool Initialize(HWND hwnd, int windowWidth, int windowHeight) = 0;

	virtual void ClearRenderTargetView() = 0;
	virtual void ClearDepthStencilView() = 0;
	virtual void PresentFrame() = 0;

protected:
	float m_clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
};

class Renderer
{
public:
	enum eGraphicsAPIs
	{
		D3D_11,
		D3D_12
	};

public:
	Renderer() {}
	bool Initialize(HWND hwnd, eGraphicsAPIs targetAPI, int windowWidth, int windowHeight);
	void ClearRenderTargetView();
	void ClearDepthStencilView();
	void PresentFrame();

private:
	GraphicsAPI* m_pActiveAPI = nullptr;

	int m_windowWidth = 0;
	int m_windowHeight = 0;
};

class Direct3D_11 : public GraphicsAPI
{
public:
	Direct3D_11() {}
	bool Initialize(HWND hwnd, int windowWidth, int windowHeight) override;

	void ClearRenderTargetView() override;
	void ClearDepthStencilView() override;
	void PresentFrame() override;

private:

	// Device
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