//
// Created by Revolware Company on 2019-09-06.
//

#include "Instructions.h"
#include "InstructionTable.h"
#include "CbInstructionTable.h"
#include "Operations/Pc.h"
#include "Log.h"

uint64_t Instructions::execute(GameBoy &gameBoy) const noexcept
{
	return decodeInstruction(gameBoy).execute(gameBoy);
}

Instruction Instructions::decodeInstruction(GameBoy &gameBoy) const noexcept
{
	const auto instruction = PcOperations::loadByte(gameBoy);

	Log::info(m_instructionNameTable + (size_t(instruction) << InstructionNameOffset), "\n");

	return Instruction{m_instructionTable[instruction]};
}

Instructions Instructions::Create() noexcept
{
	return Instructions(InstructionTable, reinterpret_cast<const char *>(InstructionNameTable));
}

Instructions Instructions::CreateCbPrefix() noexcept
{
	return Instructions(CbInstructionTable, reinterpret_cast<const char *>(CbInstructionNameTable));
}

Instructions::Instructions(const Instruction::Handler *instructionTable, const char *instructionNameTable) noexcept :
		m_instructionTable{instructionTable},
		m_instructionNameTable{instructionNameTable} {}
