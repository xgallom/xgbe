//
// Created by Revolware Company on 2019-09-06.
//

#include "Instruction.h"

uint64_t Instruction::execute(GameBoy &gameBoy) const noexcept
{
	return (*m_handler)(gameBoy);
}
