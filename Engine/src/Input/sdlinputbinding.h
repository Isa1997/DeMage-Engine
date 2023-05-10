#pragma once
#include <map>

namespace Engine
{
	inline static const std::map<std::string, SDL_Scancode> g_KeyboardMap =
	{
		// Letter mapping
		{"A" , SDL_Scancode::SDL_SCANCODE_A},
		{"B" , SDL_Scancode::SDL_SCANCODE_B},
		{"C" , SDL_Scancode::SDL_SCANCODE_C},
		{"D" , SDL_Scancode::SDL_SCANCODE_D},
		{"E" , SDL_Scancode::SDL_SCANCODE_E},
		{"F" , SDL_Scancode::SDL_SCANCODE_F},
		{"G" , SDL_Scancode::SDL_SCANCODE_G},
		{"H" , SDL_Scancode::SDL_SCANCODE_H},
		{"I" , SDL_Scancode::SDL_SCANCODE_I},
		{"J" , SDL_Scancode::SDL_SCANCODE_J},
		{"K" , SDL_Scancode::SDL_SCANCODE_K},
		{"L" , SDL_Scancode::SDL_SCANCODE_L},
		{"M" , SDL_Scancode::SDL_SCANCODE_M},
		{"N" , SDL_Scancode::SDL_SCANCODE_N},
		{"O" , SDL_Scancode::SDL_SCANCODE_O},
		{"P" , SDL_Scancode::SDL_SCANCODE_P},
		{"Q" , SDL_Scancode::SDL_SCANCODE_Q},
		{"R" , SDL_Scancode::SDL_SCANCODE_R},
		{"S" , SDL_Scancode::SDL_SCANCODE_S},
		{"T" , SDL_Scancode::SDL_SCANCODE_T},
		{"U" , SDL_Scancode::SDL_SCANCODE_U},
		{"V" , SDL_Scancode::SDL_SCANCODE_V},
		{"W" , SDL_Scancode::SDL_SCANCODE_W},
		{"X" , SDL_Scancode::SDL_SCANCODE_X},
		{"Y" , SDL_Scancode::SDL_SCANCODE_Y},
		{"Z" , SDL_Scancode::SDL_SCANCODE_Z},

		// Number mappings
		{"1" , SDL_Scancode::SDL_SCANCODE_1},
		{"2" , SDL_Scancode::SDL_SCANCODE_2},
		{"3" , SDL_Scancode::SDL_SCANCODE_3},
		{"4" , SDL_Scancode::SDL_SCANCODE_4},
		{"5" , SDL_Scancode::SDL_SCANCODE_5},
		{"6" , SDL_Scancode::SDL_SCANCODE_6},
		{"7" , SDL_Scancode::SDL_SCANCODE_7},
		{"8" , SDL_Scancode::SDL_SCANCODE_8},
		{"9" , SDL_Scancode::SDL_SCANCODE_9},
		{"0" , SDL_Scancode::SDL_SCANCODE_0},

		//Arrows
		{"ARROW_UP" , SDL_Scancode::SDL_SCANCODE_UP},
		{"ARROW_DOWN" , SDL_Scancode::SDL_SCANCODE_DOWN},
		{"ARROW_LEFT" , SDL_Scancode::SDL_SCANCODE_LEFT},
		{"ARROW_RIGHT" , SDL_Scancode::SDL_SCANCODE_RIGHT},

		//Specials
		{"RETURN" , SDL_Scancode::SDL_SCANCODE_RETURN},
		{"ESCAPE" , SDL_Scancode::SDL_SCANCODE_ESCAPE},
		{"BACKSPACE" , SDL_Scancode::SDL_SCANCODE_BACKSPACE},
		{"TAB" , SDL_Scancode::SDL_SCANCODE_TAB},
		{"SPACE" , SDL_Scancode::SDL_SCANCODE_SPACE}
	};
	
	inline static const std::map<std::string, SDL_GameControllerButton> g_ControllerMapping =
	{
		// Buttons
		{"A" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A},
		{"B" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B},
		{"X" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X},
		{"Y" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y},

		// Controll buttons
		{"BACK" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK},
		{"START" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START},

		// Shoulders
		{"LEFTSHOULDER" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER},
		{"RIGHTSHOULDER" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER},

		//DPad
		{"DPAD_UP" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP},
		{"DPAD_DOWN" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN},
		{"DPAD_LEFT" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT},
		{"DPAD_RIGHT" , SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT}
	};

	inline static const std::map<std::string, SDL_GameControllerAxis> g_ControllerAxisMapping =
	{
		// Left stick
		{"LS_UP" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY},
		{"LS_DOWN" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY},
		{"LS_LEFT" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX},
		{"LS_RIGHT" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX},

		// Right stick
		{"RS_UP" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY},
		{"RS_DOWN" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY},
		{"RS_LEFT" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX},
		{"RS_RIGHT" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX},

		// Triggers
		{"TRIGGER_LEFT" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT},
		{"TRIGGER_RIGHT" , SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT}
	};
}