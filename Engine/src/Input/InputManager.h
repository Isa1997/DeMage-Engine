#pragma once

#include "Input/InputAction.h"
#include "Input/inputenums.h"
#include "Input/inputbinding.h"

namespace Engine
{
    class EntityManager;
    struct InputComponent;

    class InputManager
    {
    public:
        bool Init();
        void Update(float dt, EntityManager* entityManager);
        void Shutdown();

        void SwitchActiveInputSource(EInputSource newSource);
        void ToggleActiveInputSource();

        static bool IsActionActive(InputComponent* inputComponent, EInputAction targetAction);

        InputManager() = default;

    private:
        void ProcessInput();
        bool IsButtonActionActive(EInputAction _eAction, EInputActionState _eState) const;
        void InitKeybinds();

        void InitActiveController();

        SDL_GameController* m_ActiveController = nullptr;

        std::unordered_map<EInputAction, InputBinding> m_InputActions{ };
        std::unordered_map<EInputAction, EInputActionState> m_InputActionStates{ };

        EInputSource m_InputSource{ EInputSource::Keyboard };

        InputManager(const InputManager& other) = delete;
        InputManager& operator=(InputManager& other) = delete;
    };
}
