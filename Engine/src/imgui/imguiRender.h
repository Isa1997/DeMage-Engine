#pragma once 

#ifdef IMGUI
#include "src/Render/Renderer.h"

class ImguiRender
{
public:
	bool Init(const Engine::Renderer& renderer);
	void Shutdown();
	void Render();
};
#endif