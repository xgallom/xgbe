//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_BIT_H
#define XGBE_BIT_H

#include "Operands.h"
#include "Operations/Flag.h"

template<typename Op, uint8_t Bit, uint64_t Cycles = 8>
inline uint64_t BIT(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	static constexpr auto Mask = uint8_t(1u << Bit);

	const auto bit = Op::Read(gameBoy) & Mask;

	FlagOperations::setZF(gameBoy, bit);
	FlagOperations::clearNF(gameBoy);
	FlagOperations::setHF(gameBoy);

	return Cycles;
}

template<typename Op, uint8_t Bit, uint64_t Cycles = 8>
inline uint64_t RES(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	static constexpr auto Mask = uint8_t(~(1u << Bit));

	const auto op = Op::Read(gameBoy);
	Op::Write(gameBoy, op & Mask);

	return Cycles;
}

template<typename Op, uint8_t Bit, uint64_t Cycles = 8>
inline uint64_t SET(GameBoy &gameBoy) noexcept
{
	static_assert(isByte<Op>(), "Operand width must be byte");

	static constexpr auto Mask = uint8_t(1u << Bit);

	const auto op = Op::Read(gameBoy);
	Op::Write(gameBoy, op | Mask);

	return Cycles;
}

#endif //XGBE_BIT_H
