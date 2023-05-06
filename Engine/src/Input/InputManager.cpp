#include "precomp.h"

#include "InputManager.h"

#include "src/ECS/EntityManager.h"
#include "src/Input/sdlinputbinding.h"

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
        if (m_InputActionStates.find(_eAction) == m_InputActionStates.end())
        {
            ASSERT(m_InputActionStates.find(_eAction) != m_InputActionStates.end(), "Unknown input action: {}", _eAction);
            return false;
        }

        return m_InputActionStates.at(_eAction) == _eState;
    }

    void InputManager::InitKeybinds()
    {
        m_InputActionStates.clear();
        m_InputActions.clear();

        ProcessJSON(ReadFile(s_BindingInputFile));
    }

    void InputManager::ProcessJSON(json input)
    {
        if (input.empty() || input.is_discarded())
        {
            LOG_CRITICAL("json input is invalid! Could not initialize input bindings!");
            return;
        }
        
        const auto& controlls = input["Controlls"];

        for (const auto& controll : controlls)
        {
            std::string controllName = controll["Name"];

            const auto& binding  = controll["Bindings"];
            std::string keyboard = binding["Keyboard"];
            std::string controller = binding["Controller"];

            SDL_Scancode keyboardCode = FindKeyboardSDLBinding(keyboard);
            SDL_GameControllerButton controllerCode = FindControllerSDLBinding(controller);

            m_InputActions[controllName] = { keyboardCode, controllerCode };
        }
    }

    SDL_Scancode InputManager::FindKeyboardSDLBinding(const std::string& input) const
    {
        SDL_Scancode keyboardCode = SDL_Scancode::SDL_SCANCODE_UNKNOWN;
        const auto& mapping = g_KeyboardMap.find(input);
        if (mapping == g_KeyboardMap.end())
        {
            LOG_CRITICAL("Could not find controll Name in mapping! ControllName = %s", input);
        }
        else
        {
            keyboardCode = mapping->second;
        }
        return keyboardCode;
    }

    SDL_GameControllerButton InputManager::FindControllerSDLBinding(const std::string& input) const
    {
        SDL_GameControllerButton controllerCode = SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID;
        const auto& controllerMapping = g_ControllerMapping.find(input);
        if (controllerMapping == g_ControllerMapping.end())
        {
            LOG_CRITICAL("Could not find controll Name in mapping! ControllName = %s", input);
        }
        else
        {
            controllerCode = controllerMapping->second;
        }
        return controllerCode;
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
