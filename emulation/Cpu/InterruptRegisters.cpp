//
// Created by Revolware Company on 2019-09-07.
//

#include "InterruptRegisters.h"

void InterruptRegisters::reset() noexcept
{
	m_registers[IME] = m_registers[IE] = m_registers[IF] = 0;
}
