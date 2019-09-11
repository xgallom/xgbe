//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_SUBSTRACTION_H
#define XGBE_SUBSTRACTION_H

#include "Operations/Flag.h"

template<typename Op, uint64_t Cycles = 4>
inline uint64_t SUB(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be a byte");

	auto &A = RegisterOperations::refA(gameBoy);
	const uint8_t op = -Op::Read(gameBoy);

	const uint16_t result = A + op;
	const uint8_t byteResult = result;

	FlagOperations::setZF(gameBoy, byteResult);
	FlagOperations::setNF(gameBoy);
	FlagOperations::doubleOperandHF(gameBoy, A, op);
	FlagOperations::setCF(gameBoy, result);

	A = byteResult;

	return Cycles;
}

template<typename Op, uint64_t Cycles = 4>
inline uint64_t SBC(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be a byte");

	auto &A = RegisterOperations::refA(gameBoy);
	const uint8_t op = -Op::Read(gameBoy);

	const uint16_t result = A + op + (FlagOperations::getCF(gameBoy) ? 0xffffu : 0);
	const uint8_t byteResult = result;

	FlagOperations::setZF(gameBoy, byteResult);
	FlagOperations::setNF(gameBoy);
	FlagOperations::singleOperandHF(gameBoy, A, byteResult);
	FlagOperations::setCF(gameBoy, result);

	A = byteResult;

	return Cycles;
}

#endif //XGBE_SUBSTRACTION_H
