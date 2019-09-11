//
// Created by Revolware Company on 2019-09-07.
//

#include "MemoryBankController.h"

Result<uint8_t> MemoryBankController::read(GameBoy &gameBoy, uint16_t address) const noexcept
{
	return (*m_readHandler)(gameBoy, m_data.get(), address);
}

bool MemoryBankController::write(GameBoy &gameBoy, uint16_t address, uint8_t value) const noexcept
{
	return (*m_writeHandler)(gameBoy, m_data.get(), address, value);
}

MemoryBankController::MemoryBankController(ReadHandler readHandler, WriteHandler writeHandler) noexcept :
		m_readHandler{readHandler},
		m_writeHandler{writeHandler} {}

MemoryBankController::MemoryBankController(
		ReadHandler readHandler,
		WriteHandler writeHandler,
		std::unique_ptr<Data> &&data
) noexcept :
		m_readHandler{readHandler},
		m_writeHandler{writeHandler},
		m_data{std::move(data)} {}
