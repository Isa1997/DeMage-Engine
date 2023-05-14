#pragma once 

#ifdef IMGUI
#include "src/Render/Renderer.h"

class ImguiRender
{
public:
	bool Init(const Engine::Renderer& renderer);
	void Shutdown();
	void Render();
	void SetIsActive(bool isActive);
	bool GetIsActive() const;

private:
	bool m_IsActive{ true };
};
#endif