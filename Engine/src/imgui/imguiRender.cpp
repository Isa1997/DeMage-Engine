#include "precomp.h"

#include "src/imgui/imguiRender.h"

#ifdef IMGUI

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer.h>

bool ImguiRender::Init(const Engine::Renderer& renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io{ ImGui::GetIO() };

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplSDL2_InitForSDLRenderer(renderer.GetNativeWindow(), renderer.GetNativeRenderer());
    ImGui_ImplSDLRenderer_Init(renderer.GetNativeRenderer());

    return true;
}

void ImguiRender::Shutdown()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ImguiRender::Render()
{
    if (m_IsActive == false)
        return;

    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Some panel");
    ImGui::Text("Hello World");
    ImGui::End();


    ImGui::Render();

    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void ImguiRender::SetIsActive(bool isActive)
{
    m_IsActive = isActive;
}

bool ImguiRender::GetIsActive() const
{
    return m_IsActive;
}
#endif