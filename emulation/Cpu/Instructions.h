//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_INSTRUCTIONS_H
#define XGBE_INSTRUCTIONS_H

#include "Instruction.h"

class Instructions {
public:
	static constexpr size_t InstructionsCount = 0x100, MaxInstructionNameSize = 32, InstructionNameOffset = 5;

	uint64_t execute(GameBoy &gameBoy) const noexcept;

	static Instructions Create() noexcept;
	static Instructions CreateCbPrefix() noexcept;

private:
	Instruction decodeInstruction(GameBoy &gameBoy) const noexcept;

	explicit Instructions(const Instruction::Handler *instructionTable, const char *instructionNameTable) noexcept;

	const Instruction::Handler *m_instructionTable = nullptr;
	const char *m_instructionNameTable = nullptr;
};


#endif //XGBE_INSTRUCTIONS_H
