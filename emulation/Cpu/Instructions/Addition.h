//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_ADDITION_H
#define XGBE_ADDITION_H

#include "Operations/Flag.h"

template<typename Op1, typename Op2, uint64_t Cycles = 4, EnableIf<isByte<Op1>()> = true>
inline uint64_t ADD(GameBoy &gameBoy) noexcept
{
	static_assert(Op1::Width == Op2::Width, "Operands widths must be compatible");

	const auto op1 = Op1::Read(gameBoy), op2 = Op2::Read(gameBoy);
	const uint16_t result = op1 + op2;
	const uint8_t byteResult = result;

	Op1::Write(gameBoy, byteResult);

	FlagOperations::setZF(gameBoy, byteResult);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::doubleOperandHF(gameBoy, op1, op2);
	FlagOperations::setCF(gameBoy, result);

	return Cycles;
}

template<typename Op1, typename Op2, uint64_t Cycles = 4, EnableIf<isWord<Op1>()> = true>
inline uint64_t ADD(GameBoy &gameBoy) noexcept
{
	static_assert(Op1::Width == Op2::Width, "Operands widths must be compatible");

	const auto op1 = Op1::Read(gameBoy), op2 = Op2::Read(gameBoy);
	const uint32_t result = op1 + op2;
	const uint16_t wordResult = result;

	Op1::Write(gameBoy, wordResult);

	FlagOperations::clearNF(gameBoy);
	FlagOperations::doubleOperandHF(gameBoy, op1, op2);
	FlagOperations::setCF(gameBoy, result);

	return Cycles;
}

template<typename Op1, typename Op2, uint64_t Cycles = 4, EnableIf<isByte<Op1>()> = true>
inline uint64_t ADC(GameBoy &gameBoy) noexcept
{
	static_assert(Op1::Width == Op2::Width, "Operands widths must be compatible");

	const auto op1 = Op1::Read(gameBoy), op2 = Op2::Read(gameBoy);
	const uint16_t result = op1 + op2 + (FlagOperations::getCF(gameBoy) ? 1u : 0u);
	const uint8_t byteResult = result;

	Op1::Write(gameBoy, byteResult);

	FlagOperations::setZF(gameBoy, byteResult);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::doubleOperandHF(gameBoy, op1, op2);
	FlagOperations::setCF(gameBoy, result);

	return Cycles;
}

#endif //XGBE_ADDITION_H
