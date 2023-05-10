#pragma once

#include "src/IJSONParser/ijsonparser.h"
#include "src/Input/InputAction.h"
#include "src/Input/inputenums.h"
#include "src/Input/inputbinding.h"

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>

namespace Engine
{
    class EntityManager;
    struct InputComponent;

    class InputManager : public IJSONParser
    {
    public:
        inline static const std::string s_BindingInputFile = "./Data/Input/input_config.json";
    public:
        InputManager() = default;

        bool Init();
        void Update(float dt, EntityManager* entityManager);
        void Shutdown();

        void SwitchActiveInputSource(EInputSource newSource);
        void ToggleActiveInputSource();
        void UpdateAxisValues(unsigned index, long int value);

        static bool IsActionActive(InputComponent* inputComponent, EInputAction targetAction);

        void ProcessJSON(json input) override;

    private:
        void ProcessInput();
        bool IsButtonActionActive(EInputAction _eAction, EInputActionState _eState) const;
        void InitKeybinds();
        void InitActiveController();

        SDL_Scancode FindKeyboardSDLBinding(const std::string& input) const;
        SDL_GameControllerButton FindControllerSDLBinding(const std::string& input) const;
        SDL_GameControllerAxis FindAxisSDLBinding(const std::string& input) const;

        SDL_GameController* m_ActiveController = nullptr;

        std::unordered_map<EInputAction, InputBinding> m_InputActions{ };
        std::unordered_map<EInputAction, EInputActionState> m_InputActionStates{ };

        std::unordered_map<SDL_GameControllerAxis, long int> m_AxisValues;

        EInputSource m_InputSource{ EInputSource::Keyboard };

        InputManager(const InputManager& other) = delete;
        InputManager& operator=(InputManager& other) = delete;
    };
}
