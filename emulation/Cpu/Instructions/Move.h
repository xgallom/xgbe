//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_INSTRUCTIONSMOVE_H
#define XGBE_INSTRUCTIONSMOVE_H

#include "Operands.h"

template<typename Op1, typename Op2, uint64_t Cycles>
inline uint64_t LD(GameBoy &gameBoy) noexcept
{
	static_assert(Op1::Width == Op2::Width, "Operands widths must be compatible");
	Op1::Write(gameBoy, Op2::Read(gameBoy));
	return Cycles;
}

inline uint64_t LD_HL_SP_R8(GameBoy &gameBoy) noexcept
{
	const uint32_t sp = SP::Read(gameBoy);
	const auto relative = D8::Read(gameBoy);
	const uint32_t address = sp + int16_t(relative);

	HL::Write(gameBoy, uint16_t(address));

	FlagOperations::clearZF(gameBoy);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::doubleOperandHF(gameBoy, sp, relative);
	FlagOperations::setCF(gameBoy, address);

	return 12;
}

#endif //XGBE_INSTRUCTIONSMOVE_H
