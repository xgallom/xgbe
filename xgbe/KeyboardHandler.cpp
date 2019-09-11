//
// Created by Revolware Company on 2019-09-05.
//

#include "KeyboardHandler.h"
#include "Emulation.h"

#include <SDL2/SDL_events.h>

KeyHandleCommand::Enum KeyboardHandler::handleKeyEvent(Emulation &emulation, const SDL_KeyboardEvent &keyboardEvent)
{
	if(!keyboardEvent.repeat) {
		const int32_t keyCode = keyboardEvent.keysym.sym;

		for(auto n = 0; n < KeyCommand::Size; ++n) {
			if(m_keyCodes[n] == keyCode)
				return static_cast<KeyHandleCommand::Enum>(n);
		}

		switch(keyCode) {
			case SDLK_SPACE:
				return KeyHandleCommand::PauseOrResume;
			case SDLK_b:
				return KeyHandleCommand::Step;
			case SDLK_ESCAPE:
				return KeyHandleCommand::Quit;

			default:
				break;
		}
	}

	return KeyHandleCommand::Unhandled;
}

