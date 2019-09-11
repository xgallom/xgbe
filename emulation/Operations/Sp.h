//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_SP_Operations_H
#define XGBE_SP_Operations_H

#include "Bus.h"

namespace SpOperations {
	inline uint8_t popByte(GameBoy &gameBoy) noexcept
	{
		const auto address = gameBoy.cpu().registers().adv<CpuRegisters::SP>();
		return BusOperations::readByte(gameBoy, address);
	}

	inline uint16_t popWord(GameBoy &gameBoy) noexcept
	{
		const auto address = gameBoy.cpu().registers().advTwo<CpuRegisters::SP>();
		return BusOperations::readWord(gameBoy, address);
	}

	inline void pushByte(GameBoy &gameBoy, uint16_t value) noexcept
	{
		const auto address = gameBoy.cpu().registers().red<CpuRegisters::SP>();
		BusOperations::writeByte(gameBoy, address, value);
	}

	inline void pushWord(GameBoy &gameBoy, uint16_t value) noexcept
	{
		const auto address = gameBoy.cpu().registers().redTwo<CpuRegisters::SP>();
		BusOperations::writeWord(gameBoy, address, value);
	}
}

#endif //XGBE_SP_H
