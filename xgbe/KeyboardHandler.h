//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_KEYBOARDHANDLER_H
#define XGBE_KEYBOARDHANDLER_H

#include "KeyHandleCommand.h"
#include "KeyCommand.h"

#include <cstddef>
#include <cstdint>

class SDL_KeyboardEvent;
class Emulation;

class KeyboardHandler {
public:
	using KeyPressHandler = void (*)(Emulation &emulation);

	KeyHandleCommand::Enum handleKeyEvent(Emulation &emulation, const SDL_KeyboardEvent &keyboardEvent);

private:
	uint32_t m_keyCodes[KeyCommand::Size] = {'w', 'a', 's', 'd', 'j', 'k', 'c', 'v'};
};


#endif //XGBE_KEYBOARDHANDLER_H
