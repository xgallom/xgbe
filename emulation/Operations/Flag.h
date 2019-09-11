//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_FLAG_OPERATIONS_H
#define XGBE_FLAG_OPERATIONS_H

#include "GameBoy.h"

namespace FlagOperations {
	inline void setZF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().set<CpuRegisters::ZF>(); }
	inline void clearZF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().clear<CpuRegisters::ZF>(); }

	inline void setZF(GameBoy &gameBoy, uint8_t result) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::ZF>(result != 0);
	}

	inline void setNF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().set<CpuRegisters::NF>(); }
	inline void clearNF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().clear<CpuRegisters::NF>(); }

	inline void setHF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().set<CpuRegisters::HF>(); }
	inline void clearHF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().clear<CpuRegisters::HF>(); }
	inline bool getHF(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().read<CpuRegisters::HF>(); }

	inline void singleOperandHF(GameBoy &gameBoy, uint8_t previous, uint8_t result) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::HF>(((previous ^ result) & 0x10u) != 0);
	}

	inline void doubleOperandHF(GameBoy &gameBoy, uint8_t op1, uint8_t op2) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::HF>((op1 & op2 & 0x08u) != 0);
	}

	inline void setCF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().set<CpuRegisters::CF>(); }
	inline void clearCF(GameBoy &gameBoy) noexcept { gameBoy.cpu().registers().clear<CpuRegisters::CF>(); }
	inline bool getCF(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().read<CpuRegisters::CF>(); }

	inline void setCF(GameBoy &gameBoy, bool result) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::CF>(result);
	}

	inline void setCF(GameBoy &gameBoy, uint16_t result) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::CF>((result & 0x10u) != 0);
	}

	inline void setCF(GameBoy &gameBoy, uint32_t result) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::CF>((result & 0x100u) != 0);
	}

	inline void invertCF(GameBoy &gameBoy) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::CF>(!gameBoy.cpu().registers().read<CpuRegisters::CF>());
	}
}

#endif //XGBE_FLAG_OPERATIONS_H
