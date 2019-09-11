//
// Created by Revolware Company on 2019-09-06.
//

#include "CbInstruction.h"
#include <Cpu/Instructions.h>

uint64_t CbInstruction(GameBoy &gameBoy) noexcept
{
	static const auto cbInstruction = Instructions::CreateCbPrefix();
	return cbInstruction.execute(gameBoy);
}
