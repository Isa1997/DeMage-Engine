#include "precomp.h"

#include "InputManager.h"

#include "ECS/EntityManager.h"
#include <SDL2/SDL_gamecontroller.h>

namespace Engine
{
    bool KeyDown(KeyboardButton iKey)
    {
        const unsigned char* state = SDL_GetKeyboardState(nullptr);
        return state[static_cast<int>(iKey)] != 0;
    }

    bool ControllerButtonDown(SDL_GameController* controller, ControllerButton iButton)
    {
        return SDL_GameControllerGetButton(controller, iButton);
    }

    bool InputManager::Init()
    {
        LOG_INFO("Initializing InputManager");

        InitKeybinds();
        InitActiveController();

        return true;
    }

    void InputManager::SwitchActiveInputSource(EInputSource newSource)
    {
        if (newSource == m_InputSource)
            return;

        if (newSource == EInputSource::Controller)
        {
            InitActiveController();
            if (m_ActiveController == nullptr)
                return;
        }

        m_InputSource = newSource;
    }

    void InputManager::ToggleActiveInputSource()
    {
        if (m_InputSource == EInputSource::Keyboard)
        {
            SwitchActiveInputSource(EInputSource::Controller);
        }
        else
        {
            SwitchActiveInputSource(EInputSource::Keyboard);
        }
    }

    void InputManager::InitActiveController()
    {
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            if (SDL_IsGameController(i))
            {
                m_ActiveController = SDL_GameControllerOpen(i);
                break;
            }
        }
    }

    void InputManager::ProcessInput()
    {
        for (auto& [action, key] : m_InputActions)
        {
            bool isPressed = false;
            if (m_InputSource == EInputSource::Keyboard)
            {
                isPressed = KeyDown(key.m_KeyboardButton);
            }
            else if (m_InputSource == EInputSource::Controller && m_ActiveController != nullptr)
            {
                isPressed = ControllerButtonDown(m_ActiveController, key.m_ControllerButton) == 1 ? true : false;
            }

            switch (m_InputActionStates[action])
            {
            case EInputActionState::None:
            {
                m_InputActionStates[action] = isPressed ? EInputActionState::JustPressed : EInputActionState::None;
                break;
            }
            case EInputActionState::JustPressed:
            case EInputActionState::Pressed:
            {
                m_InputActionStates[action] = isPressed ? EInputActionState::Pressed : EInputActionState::Released;
                break;
            }
            case EInputActionState::Released:
            {
                m_InputActionStates[action] = isPressed ? EInputActionState::JustPressed : EInputActionState::None;
                break;
            }
            default:
                //ASSERT("Unknown EInputActionState {0}", m_InputActionStates[action]);
                m_InputActionStates[action] = EInputActionState::None;
                break;
            }
        }
    }

    void InputManager::Update(float dt, EntityManager* entityManager)
    {
        ProcessInput();

        // Update entities
        auto inputComponents = entityManager->GetAllComponentInstances<InputComponent>();

        for (auto component : inputComponents)
        {
            for (auto& action : component->inputActions)
            {
                action.m_Active = IsButtonActionActive(action.m_Action, action.m_ActionTriggerState);
            }
        }
    }

    void InputManager::Shutdown()
    {
        m_InputActions.clear();
        m_InputActionStates.clear();

        if (m_ActiveController != nullptr)
        {
            SDL_GameControllerClose(m_ActiveController);
            m_ActiveController = nullptr;
        }
    }

    bool InputManager::IsButtonActionActive(EInputAction _eAction, EInputActionState _eState) const
    {
        ASSERT(m_InputActionStates.find(_eAction) != m_InputActionStates.end(), "Unknown input action: {}", _eAction);
        return m_InputActionStates.at(_eAction) == _eState;
    }

    void InputManager::InitKeybinds()
    {
        m_InputActionStates.clear();
        m_InputActions.clear();

        m_InputActions["PlayerMoveUp"] = { SDL_SCANCODE_UP, SDL_CONTROLLER_BUTTON_DPAD_UP };
        m_InputActions["PlayerMoveLeft"] = { SDL_SCANCODE_LEFT, SDL_CONTROLLER_BUTTON_DPAD_LEFT };
        m_InputActions["PlayerMoveDown"] = { SDL_SCANCODE_DOWN, SDL_CONTROLLER_BUTTON_DPAD_DOWN };
        m_InputActions["PlayerMoveRight"] = { SDL_SCANCODE_RIGHT, SDL_CONTROLLER_BUTTON_DPAD_RIGHT};
        m_InputActions["PauseGame"] = { SDL_SCANCODE_P, SDL_CONTROLLER_BUTTON_BACK };
  
    }

    bool InputManager::IsActionActive(InputComponent* inputComponent, EInputAction targetAction)
    {
        auto found = std::find_if(
            std::begin(inputComponent->inputActions),
            std::end(inputComponent->inputActions),
            [targetAction](Engine::InputAction e)
        {
            return e.m_Action == targetAction && e.m_Active == true;
        });

        return found != std::end(inputComponent->inputActions);
    }
}
