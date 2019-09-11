//
// Created by Revolware Company on 2019-09-05.
//

#include "CpuRegisters.h"

void CpuRegisters::reset() noexcept
{
	m_words[AF] = m_words[BC] = m_words[DE] = m_words[HL] = m_words[SP] = m_words[PC] = 0u;
}
