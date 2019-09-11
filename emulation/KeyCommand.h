//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_KEYCOMMAND_H
#define XGBE_KEYCOMMAND_H

#include <cstddef>

namespace KeyCommand {
	enum Enum {
		None = -1,

		Up = 0,
		Left,
		Down,
		Right,
		A,
		B,
		Select,
		Start,
	};

	static constexpr size_t Size = Start + 1;
}

#endif //XGBE_KEYCOMMAND_H
