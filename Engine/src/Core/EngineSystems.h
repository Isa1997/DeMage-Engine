#pragma once

#include "src/Audio/AudioSystem.h"
#include "src/ECS/EntityManager.h"
#include "src/Input/InputManager.h"
#include "src/Physics/PhysicsSystem.h"
#include "src/Render/RenderSystem.h"
#include "src/Render/WindowData.h"
#include "src/Render/TextureManager.h"

namespace Engine
{
	struct WindowData;

	struct EngineSystems
	{
	public:

		bool Init(const WindowData& windowData);
		bool Update(float dt);
		bool Shutdown();

		std::unique_ptr<AudioSystem> m_AudioSystem{};
		std::unique_ptr<EntityManager> m_EntityManager{};
		std::unique_ptr<InputManager> m_InputManager{};
		std::unique_ptr<TextureManager> m_TextureManager{};
		std::unique_ptr<PhysicsSystem> m_PhysicsSystem{};
		std::unique_ptr<RenderSystem> m_RenderSystem{};
	};
}

