#pragma once

#include <SDL2/SDL_gamecontroller.h>

using KeyboardButton = int;
using ControllerButton = SDL_GameControllerButton;
using ControllerAxis = SDL_GameControllerAxis;

namespace Engine
{
	struct ControllerBinding
	{
		ControllerButton m_ControllerButton;

		ControllerAxis m_Axis = SDL_CONTROLLER_AXIS_INVALID;
		long int m_ThreshholdValue = 0;
	};

	struct InputBinding
	{
		KeyboardButton m_KeyboardButton;
		ControllerBinding m_ControllerBinding;
	};
}