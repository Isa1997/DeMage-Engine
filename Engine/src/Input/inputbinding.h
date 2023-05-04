#pragma once

#include <SDL2/SDL_gamecontroller.h>

using KeyboardButton = int;
using ControllerButton = SDL_GameControllerButton;

namespace Engine
{
	struct InputBinding
	{
		KeyboardButton m_KeyboardButton;
		ControllerButton m_ControllerButton;
	};
}