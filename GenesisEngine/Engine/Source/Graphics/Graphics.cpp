#include "Graphics.h"
#include "..\Error.h"

bool Graphics::Initialize(HWND hwnd, int windowWidth, int windowHeight)
{

	if(!m_renderer.Initialize(hwnd, Renderer::eGraphicsAPIs::D3D_11, windowWidth, windowHeight))
		return false;


	return true;
}

void Graphics::RenderFrame()
{
	m_renderer.ClearRenderTargetView();
	m_renderer.ClearDepthStencilView();

	// TODO: Place draw code here

	m_renderer.PresentFrame();
	
}
