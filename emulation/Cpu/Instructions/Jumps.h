//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_JUMPS_H
#define XGBE_JUMPS_H

#include "Flags.h"
#include "Operations/Sp.h"

inline uint64_t RET(GameBoy &gameBoy) noexcept
{
	PcOperations::store(gameBoy, SpOperations::popWord(gameBoy));
	return 16;
}

template<typename Flag>
inline uint64_t RET(GameBoy &gameBoy) noexcept
{
	static_assert(isBit<Flag>(), "Conditional operations must have flag operands");

	if(Flag::Read(gameBoy)) {
		RET(gameBoy);
		return 20;
	}

	return 8;
}

inline uint64_t RETI(GameBoy &gameBoy) noexcept
{
	RET(gameBoy);
	EI(gameBoy);

	return 16;
}

template<typename Op>
inline uint64_t CALL(GameBoy &gameBoy) noexcept
{
	static_assert(isWord<Op>(), "Operand must be an address");

	const auto address = Op::Read(gameBoy);
	SpOperations::pushWord(gameBoy, PcOperations::read(gameBoy));
	PcOperations::store(gameBoy, address);

	return 24;
}

template<typename Flag, typename Op>
inline uint64_t CALL(GameBoy &gameBoy) noexcept
{
	static_assert(isBit<Flag>(), "Conditional operations must have flag operands");

	if(Flag::Read(gameBoy))
		return CALL<Op>(gameBoy);

	Op::Read(gameBoy);
	return 12;
}

template<typename Op, uint64_t Cycles>
inline uint64_t JP(GameBoy &gameBoy) noexcept
{
	static_assert(isWord<Op>(), "Operand must be an address");

	PcOperations::store(gameBoy, Op::Read(gameBoy));

	return Cycles;
}

template<typename Flag, typename Op, uint64_t CyclesJump, uint64_t CyclesContinue>
inline uint64_t JP(GameBoy &gameBoy) noexcept
{
	static_assert(isBit<Flag>(), "Conditional operations must have flag operands");

	if(Flag::Read(gameBoy))
		return JP<Op, CyclesJump>(gameBoy);

	Op::Read(gameBoy);
	return CyclesContinue;
}

template<uint16_t Address>
inline uint64_t RST(GameBoy &gameBoy) noexcept
{
	SpOperations::pushWord(gameBoy, PcOperations::read(gameBoy));
	PcOperations::store(gameBoy, Address);
	return 16;
}

#endif //XGBE_JUMPS_H
