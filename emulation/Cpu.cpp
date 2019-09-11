//
// Created by Revolware Company on 2019-09-05.
//

#include "Cpu.h"

void Cpu::reset() noexcept
{
	m_registers.reset();
}

uint64_t Cpu::runOnce(GameBoy &gameBoy) noexcept
{
	return m_instructions.execute(gameBoy);
}
