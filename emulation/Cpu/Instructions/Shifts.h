//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_SHIFTS_H
#define XGBE_SHIFTS_H

#include "Operands.h"
#include "Operations/Flag.h"

template<typename Op, uint64_t Cycles = 8>
inline uint64_t SLA(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);
	const auto bit = (op & 0x80) != 0;

	Op::Write(gameBoy, (op << 1) | (op & 0x01u));

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 8>
inline uint64_t SRA(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);
	const auto bit = (op & 0x01u) != 0;

	Op::Write(gameBoy, (op >> 1) | (op & 0x80u));

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 8>
inline uint64_t SRL(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);
	const auto bit = (op & 0x01u) != 0;

	Op::Write(gameBoy, op >> 1);

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 8>
inline uint64_t SWAP(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);

	Op::Write(gameBoy, (op << 4) | (op >> 4));

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::clearCF(gameBoy);

	return Cycles;
}

#endif //XGBE_SHIFTS_H
