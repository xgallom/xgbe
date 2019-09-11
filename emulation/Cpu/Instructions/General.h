//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_INSTRUCTIONSGENERAL_H
#define XGBE_INSTRUCTIONSGENERAL_H

#include "Operations/Flag.h"
#include "Operations/Interrupt.h"

inline uint64_t NOP(GameBoy &) noexcept { return 4; }
inline uint64_t STOP(GameBoy &) noexcept { return 4; } // TODO
inline uint64_t HALT(GameBoy &) noexcept { return 4; } // TODO

inline uint64_t DI(GameBoy &gameBoy) noexcept
{
	InterruptOperations::clearIME(gameBoy);
	return 4;
}

inline uint64_t EI(GameBoy &gameBoy) noexcept
{
	InterruptOperations::setIME(gameBoy);
	return 4;
}

inline uint64_t XXX(GameBoy &) noexcept { return Instruction::InvalidInstruction; }

#endif //XGBE_INSTRUCTIONSGENERAL_H
