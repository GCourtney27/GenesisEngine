
/////////////////////////////////////////////////////////
// Graphics takes in assets and stages them for rendering. 
// The renderer renders them to the screen. Since there can be
// multiple graphics APIs to choose from, the renderer is abstracted
// to another class. That way we can have multiple APIs for the user to 
// choose without having to wory about the nitty gritty of each rendering pipline
/////////////////////////////////////////////////////////

#pragma once
#include "Renderer.h"
#include "..\Engine.h"

class Graphics
{
public:
	Graphics() {}
	bool Initialize(HWND hwnd, int windowWidth, int windowHeight);
	void RenderFrame();

private:
	Renderer m_renderer;
	
};