//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_CPU_H
#define XGBE_CPU_H

#include "Cpu/CpuRegisters.h"
#include "Cpu/InterruptRegisters.h"
#include "Cpu/Instructions.h"
#include "Cpu/InterruptController.h"

#include <cstdint>

class GameBoy;

class Cpu {
public:
	void reset() noexcept;
	uint64_t runOnce(GameBoy &gameBoy) noexcept;

	[[nodiscard]] inline CpuRegisters &registers() noexcept { return m_registers; }
	[[nodiscard]] inline InterruptRegisters &interruptRegisters() noexcept { return m_interruptRegisters; }

private:
	CpuRegisters m_registers = {};
	InterruptRegisters m_interruptRegisters = {};
	const Instructions m_instructions = Instructions::Create();
};


#endif //XGBE_CPU_H
