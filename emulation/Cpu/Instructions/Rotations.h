//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_ROTATIONS_H
#define XGBE_ROTATIONS_H

#include "Operands.h"
#include "Operations/Flag.h"
#include "Operations/Register.h"

template<typename Op, uint64_t Cycles = 8>
inline uint64_t RL(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);
	const auto bit = (op & 0x80u) != 0;

	Op::Write(gameBoy, (op << 1u) | (bit ? 1u : 0));

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 8>
inline uint64_t RLC(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);
	const auto bit = (op & 0x80u) != 0;

	Op::Write(gameBoy, (op << 1u) | (FlagOperations::getCF(gameBoy) ? 1u : 0u));

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return Cycles;
}

inline uint64_t RLA(GameBoy &gameBoy) noexcept
{
	auto &A = RegisterOperations::refA(gameBoy);
	const auto bit = (A & 0x80u) != 0;

	A = (A << 1u) | (bit ? 1u : 0);

	FlagOperations::clearZF(gameBoy);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return 4;
}

inline uint64_t RLCA(GameBoy &gameBoy) noexcept
{
	auto &A = RegisterOperations::refA(gameBoy);
	const auto bit = (A & 0x80u) != 0;

	A = (A << 1u) | (FlagOperations::getCF(gameBoy) ? 1u : 0u);

	FlagOperations::clearZF(gameBoy);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return 4;
}

template<typename Op, uint64_t Cycles = 8>
inline uint64_t RR(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);
	const auto bit = (op & 0x01u) != 0;

	Op::Write(gameBoy, (op >> 1u) | (bit ? 0x80u : 0));

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return Cycles;
}

template<typename Op, uint64_t Cycles = 8>
inline uint64_t RRC(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	const auto op = Op::Read(gameBoy);
	const auto bit = (op & 0x01u) != 0;

	Op::Write(gameBoy, (op >> 1u) | (FlagOperations::getCF(gameBoy) ? 0x80u : 0u));

	FlagOperations::setZF(gameBoy, op);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return Cycles;
}

inline uint64_t RRA(GameBoy &gameBoy) noexcept
{
	auto &A = RegisterOperations::refA(gameBoy);
	const auto bit = (A & 0x01u) != 0;

	A = (A >> 1u) | (bit ? 0x80u : 0);

	FlagOperations::clearZF(gameBoy);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return 4;
}

inline uint64_t RRCA(GameBoy &gameBoy) noexcept
{
	auto &A = RegisterOperations::refA(gameBoy);
	const auto bit = (A & 0x01u) != 0;

	A = (A >> 1u) | (FlagOperations::getCF(gameBoy) ? 0x80u : 0u);

	FlagOperations::clearZF(gameBoy);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy, bit);

	return 4;
}

#endif //XGBE_ROTATIONS_H
