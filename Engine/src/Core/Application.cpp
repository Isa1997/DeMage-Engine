#include "precomp.h"

#include "src/Core/Application.h"

#include "src/Input/inputenums.h"
#include "src/Render/Renderer.h"
#include "src/Render/Texture.h"
#include "src/Render/Window.h"

namespace Engine 
{
    bool Application::Init()
    {
        LOG_INFO("Initializing application");

        GameSpecificWindowData();

        if (m_EngineSystem.Init(m_WindowData) != true)
        {
            LOG_CRITICAL("Error initializing game specific systems!");
            return false;
        } 
        
        if (GameSpecificInit() != true)
        {
            LOG_CRITICAL("Error initializing game specific systems!");
            return false;
        }

        return true;
    }

    bool Application::Shutdown()
    {
        LOG_INFO("Shutting down application");

        GameSpecificShutdown();

        m_EngineSystem.Shutdown();

        return true;
    }

    int Application::Run()
    {
        m_Running = true;
        auto previousFrameTime = SDL_GetPerformanceCounter();

        // Main loop
        SDL_Event event{ };
        while (m_Running)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    m_Running = false;
                }
                else if (event.type == SDL_CONTROLLERDEVICEADDED)
                {
                    m_EngineSystem.m_InputManager->SwitchActiveInputSource(EInputSource::Controller);
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.scancode == SDL_SCANCODE_K)
                    {
                        m_EngineSystem.m_InputManager->ToggleActiveInputSource();
                    }
                }
                else if (event.type == SDL_JOYAXISMOTION)
                {
                    m_EngineSystem.m_InputManager->UpdateAxisValues(event.jaxis.axis, event.jaxis.value);
                }
            }

            auto frameTime = SDL_GetPerformanceCounter();

            float deltaTime = (frameTime - previousFrameTime) / static_cast<float>(SDL_GetPerformanceFrequency());

#ifdef LOGFPS
            LOG_INFO("Current FPS: {}", 1.f / deltaTime);
#endif
            Update(deltaTime);

            previousFrameTime = frameTime;
        }

        m_Running = false;

        return 0;
    }

    void Application::Update(float dt)
    {
        m_EngineSystem.Update(dt);

        GameSpecificUpdate(dt);
    }
}
