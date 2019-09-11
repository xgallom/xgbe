//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_ADVANCE_H
#define XGBE_ADVANCE_H

#include "Operands.h"
#include "Operations/Flag.h"

template<typename Op, uint64_t Clocks = 4, EnableIf<isByte<Op>()> = true>
uint64_t INC(GameBoy &gameBoy) noexcept
{
	const auto previous = Op::Read(gameBoy);
	const auto result = previous + 1;

	Op::Write(gameBoy, result);

	FlagOperations::setZF(gameBoy, result);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::singleOperandHF(gameBoy, previous, result);

	return Clocks;
}

template<typename Op, EnableIf<isWord<Op>()> = true>
uint64_t INC(GameBoy &gameBoy) noexcept
{
	const auto result = ++Op::Ref(gameBoy);
	return 8;
}

template<typename Op, uint64_t Clocks = 4, EnableIf<isByte<Op>()> = true>
uint64_t DEC(GameBoy &gameBoy) noexcept
{
	const auto previous = Op::Read(gameBoy);
	const auto result = previous - 1;

	Op::Write(gameBoy, result);

	FlagOperations::setZF(gameBoy, result);
	FlagOperations::setNF(gameBoy);
	FlagOperations::singleOperandHF(gameBoy, previous, result);

	return Clocks;
}

template<typename Op, EnableIf<isWord<Op>()> = true>
uint64_t DEC(GameBoy &gameBoy) noexcept
{
	const auto result = --Op::Ref(gameBoy);
	return 8;
}

#endif //XGBE_ADVANCE_H
