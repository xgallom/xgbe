//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_STACK_H
#define XGBE_STACK_H

#include "Operands.h"

template<typename Op>
inline uint64_t PUSH(GameBoy &gameBoy) noexcept
{
	static_assert(isWord<Op>(), "Operand must be a word");

	SpOperations::pushWord(gameBoy, Op::Read(gameBoy));

	return 16;
}

template<typename Op>
inline uint64_t POP(GameBoy &gameBoy) noexcept
{
	static_assert(isWord<Op>(), "Operand must be a word");

	Op::Write(gameBoy, SpOperations::popWord(gameBoy));

	return 16;
}

#endif //XGBE_STACK_H
