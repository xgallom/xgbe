//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_BUS_OPERATIONS_H
#define XGBE_BUS_OPERATIONS_H

#include "GameBoy.h"

namespace BusOperations {
	inline uint8_t readByte(GameBoy &gameBoy, uint16_t address) noexcept
	{
		return gameBoy.bus().read(gameBoy, address);
	}

	inline void writeByte(GameBoy &gameBoy, uint16_t address, uint8_t value) noexcept
	{
		gameBoy.bus().write(gameBoy, address, value);
	}

	inline uint16_t readWord(GameBoy &gameBoy, uint16_t address) noexcept
	{
		return gameBoy.bus().read(gameBoy, address) |
			   (uint16_t(gameBoy.bus().read(gameBoy, address + 1)) << 8u);
	}

	inline uint16_t readWord(GameBoy &gameBoy, CpuRegisters::WordPair address) noexcept
	{
		return gameBoy.bus().read(gameBoy, address.first) |
			   (uint16_t(gameBoy.bus().read(gameBoy, address.second)) << 8u);
	}

	inline void writeWord(GameBoy &gameBoy, uint16_t address, uint16_t value) noexcept
	{
		gameBoy.bus().write(gameBoy, address, uint8_t(value));
		gameBoy.bus().write(gameBoy, address + 1, uint8_t(value >> 8u));
	}

	inline void writeWord(GameBoy &gameBoy, CpuRegisters::WordPair address, uint16_t value) noexcept
	{
		gameBoy.bus().write(gameBoy, address.first, uint8_t(value));
		gameBoy.bus().write(gameBoy, address.second, uint8_t(value >> 8u));
	}
}

#endif //XGBE_BUS_OPERATIONS_H
