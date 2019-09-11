//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_PC_OPERATIONS_H
#define XGBE_PC_OPERATIONS_H

#include "GameBoy.h"
#include "Bus.h"

namespace PcOperations {
	inline uint16_t read(GameBoy &gameBoy) noexcept
	{
		return gameBoy.cpu().registers().read<CpuRegisters::PC>();
	}

	inline uint8_t loadByte(GameBoy &gameBoy) noexcept
	{
		const auto address = gameBoy.cpu().registers().adv<CpuRegisters::PC>();
		return BusOperations::readByte(gameBoy, address);
	}

	inline uint16_t loadWord(GameBoy &gameBoy) noexcept
	{
		const auto address = gameBoy.cpu().registers().advTwo<CpuRegisters::PC>();

		return BusOperations::readWord(gameBoy, address);
	}

	inline void store(GameBoy &gameBoy, uint16_t value) noexcept
	{
		gameBoy.cpu().registers().write<CpuRegisters::PC>(value);
	}
}

#endif //XGBE_PC_OPERATIONS_H
