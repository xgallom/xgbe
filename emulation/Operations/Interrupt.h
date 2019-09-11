//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_INTERRUPT_OPERATIONS_H
#define XGBE_INTERRUPT_OPERATIONS_H

#include "GameBoy.h"

namespace InterruptOperations {
	inline bool readIME(GameBoy &gameBoy) noexcept
	{
		return gameBoy.cpu().interruptRegisters().get<InterruptRegisters::IME, InterruptRegisters::IMEBit>();
	}

	inline void setIME(GameBoy &gameBoy) noexcept
	{
		gameBoy.cpu().interruptRegisters().set<InterruptRegisters::IME, InterruptRegisters::IMEBit>();
	}

	inline void clearIME(GameBoy &gameBoy) noexcept
	{
		gameBoy.cpu().interruptRegisters().clear<InterruptRegisters::IME, InterruptRegisters::IMEBit>();
	}

	inline uint8_t readIE(GameBoy &gameBoy) noexcept
	{
		return gameBoy.cpu().interruptRegisters().read<InterruptRegisters::IE>();
	}

	inline void writeIE(GameBoy &gameBoy, uint8_t value) noexcept
	{
		gameBoy.cpu().interruptRegisters().write<InterruptRegisters::IE>(value);
	}

	inline uint8_t readIF(GameBoy &gameBoy) noexcept
	{
		return gameBoy.cpu().interruptRegisters().read<InterruptRegisters::IF>();
	}

	inline void writeIF(GameBoy &gameBoy, uint8_t value) noexcept
	{
		gameBoy.cpu().interruptRegisters().write<InterruptRegisters::IF>(value);
	}

	inline uint8_t &refIF(GameBoy &gameBoy) noexcept
	{
		return gameBoy.cpu().interruptRegisters().ref<InterruptRegisters::IF>();
	}
}

#endif //XGBE_INTERRUPT_OPERATIONS_H
