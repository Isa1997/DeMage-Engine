#pragma once

#include "src/Controller/IController.h"

namespace Game
{
    class CameraController : public Engine::IController
    {
    public:
        void Update(float dt, Engine::EngineSystems& engineSystems) override;
    };
}
