//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_AFREGISTER_H
#define XGBE_AFREGISTER_H

#include "Operations/Flag.h"
#include "Operations/Register.h"

inline uint64_t CPL(GameBoy &gameBoy) noexcept
{
	auto &A = RegisterOperations::refA(gameBoy);

	A = A ^ 0xffu;

	FlagOperations::setNF(gameBoy);
	FlagOperations::setHF(gameBoy);

	return 4;
}

inline uint64_t SCF(GameBoy &gameBoy) noexcept
{
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::setCF(gameBoy);

	return 4;
}

inline uint64_t CCF(GameBoy &gameBoy) noexcept
{
	FlagOperations::clearNF(gameBoy);
	FlagOperations::clearHF(gameBoy);
	FlagOperations::invertCF(gameBoy);

	return 4;
}

inline uint64_t DAA(GameBoy &gameBoy) noexcept
{
	auto &A = RegisterOperations::refA(gameBoy);

	uint32_t buffer = A;

	if((A & 0x0fu) > 9u || FlagOperations::getHF(gameBoy))
		buffer += 0x06;

	if((buffer >> 8u) > 9u || FlagOperations::getCF(gameBoy)) {
		buffer += 0x60;
		FlagOperations::setCF(gameBoy);
	} else
		FlagOperations::clearCF(gameBoy);

	A = buffer;

	FlagOperations::setZF(gameBoy, A);
	FlagOperations::clearHF(gameBoy);

	return 4;
}

#endif //XGBE_AFREGISTER_H
