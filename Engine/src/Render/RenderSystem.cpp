#include "precomp.h"

#include "src/Render/RenderSystem.h"

#include "src/ECS/EntityManager.h"
#include "src/Render/Renderer.h"
#include "src/Render/Window.h"

namespace Engine
{
    bool RenderSystem::Init(const WindowData& windowData_)
    {
        LOG_INFO("Initializing RenderSystem");
        SDL_SetMainReady();
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
        {
            LOG_CRITICAL("Unable to initialize SDL. SDL error: {}", SDL_GetError());
            return false;
        }
        LOG_CRITICAL("Unable to initialize SDL. SDL error: {}", SDL_GetError());
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
        {
            LOG_CRITICAL("Unable to initialize SDL_Image");
            return false;
        }

        m_Renderer = std::make_unique<Renderer>();

        if (!m_Renderer->Init(windowData_))
        {
            LOG_CRITICAL("Unable to initialize renderer");
            return false;
        }
        
#ifdef IMGUI
        m_ImguiRender = std::make_unique<ImguiRender>();

        if (!m_ImguiRender->Init(*m_Renderer.get()))
        {
            LOG_CRITICAL("Unable to initialize ImGui Renderer");
            return false;
        }
#endif

        LOG_INFO("RenderSystem initialized successfully");
        return true;
    }

    bool RenderSystem::Shutdown()
    {
        LOG_INFO("Shutting down RenderSystem");

        m_Renderer.reset();
        SDL_Quit();

        return true;
    }

    void RenderSystem::Update(float dt_, EntityManager* entityManager)
    {
        m_Renderer->BeginScene();

        // Get the main camera from the entity manager
        // TODO: Support multiple cameras and switching between them
        auto cameras = entityManager->GetAllEntitiesWithComponents<CameraComponent, TransformComponent>();
        ASSERT(!cameras.empty(), "Must have at least one camera");

        auto camera = *(cameras.begin());

        // Find all entities to draw
        auto renderables = entityManager->GetAllEntitiesWithComponents<TransformComponent, SpriteComponent>();
        m_Renderer->DrawEntities(renderables, camera);

#ifdef IMGUI
        m_ImguiRender->Render();
#endif

        m_Renderer->EndScene();
    }

    Renderer* RenderSystem::GetRenderer()
    {
        return m_Renderer.get();
    }

    void RenderSystem::SetBackgroundColor(unsigned char bgR_, unsigned char bgG_, unsigned char bgB_, unsigned char bgA_)
    {
        m_Renderer->SetBackgroundColor(bgR_, bgG_, bgB_, bgA_);
    }

    void RenderSystem::SetBackgroundColor(const Color& col_)
    {
        m_Renderer->SetBackgroundColor(col_);
    }

#ifdef IMGUI
    void RenderSystem::ToggleImGuiWindow()
    {
        m_ImguiRender->SetIsActive(!m_ImguiRender->GetIsActive());
    }
#endif
}
