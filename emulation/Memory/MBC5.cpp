//
// Created by Revolware Company on 2019-09-07.
//

#include "MemoryBankController.h"

static Result<uint8_t> read(GameBoy &gameBoy, MemoryBankController::Data *data, uint16_t address) noexcept
{
	return {};
}

static bool write(GameBoy &gameBoy, MemoryBankController::Data *data, uint16_t address, uint8_t value) noexcept
{
	return false;
}

MemoryBankController MemoryBankController::CreateMBC5() noexcept { return MemoryBankController{::read, ::write}; }
