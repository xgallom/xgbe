//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_KEYHANDLECOMMAND_H
#define XGBE_KEYHANDLECOMMAND_H

#include "KeyCommand.h"

namespace KeyHandleCommand {
	enum Enum {
		Up = 0,
		Left,
		Down,
		Right,
		A,
		B,
		Select,
		Start,

		Unhandled,

		PauseOrResume,
		Step,
		Quit
	};
}

#endif //XGBE_KEYHANDLECOMMAND_H
