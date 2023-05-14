#pragma once

#include "src/Core/EngineSystems.h"

namespace Engine
{
	class IController
	{
	public:
		virtual ~IController() = default;
		virtual void Start() {}
		virtual void Update(float dt, EngineSystems& engine) = 0;
		virtual void Shutdown() {}
	};
}