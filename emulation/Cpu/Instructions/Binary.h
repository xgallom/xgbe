//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_BINARY_H
#define XGBE_BINARY_H

template<typename Op, uint64_t Cycles = 4>
inline uint64_t AND(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be a byte");

	auto &A = RegisterOperations::refA(gameBoy);
	const uint8_t op = Op::Read(gameBoy);

	A = A & op;

	FlagOperations::setZF(gameBoy, A);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::setHF(gameBoy);
	FlagOperations::clearCF(gameBoy);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 4>
inline uint64_t XOR(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be a byte");

	auto &A = RegisterOperations::refA(gameBoy);
	const uint8_t op = Op::Read(gameBoy);

	A = A ^ op;

	FlagOperations::setZF(gameBoy, A);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::clearCF(gameBoy);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 4>
inline uint64_t OR(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be a byte");

	auto &A = RegisterOperations::refA(gameBoy);
	const uint8_t op = Op::Read(gameBoy);

	A = A | op;

	FlagOperations::setZF(gameBoy, A);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::clearCF(gameBoy);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 4>
inline uint64_t CP(GameBoy &gameBoy) noexcept
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

	return Cycles;
}

#endif //XGBE_BINARY_H
