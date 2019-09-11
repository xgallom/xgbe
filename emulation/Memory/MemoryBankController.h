//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_MEMORYBANKCONTROLLER_H
#define XGBE_MEMORYBANKCONTROLLER_H

#include "Result.h"

#include <cstdint>
#include <memory>

class GameBoy;

class MemoryBankController {
public:
	struct Data {
	};

	using ReadHandler = Result<uint8_t> (*)(GameBoy &gameBoy, Data *data, uint16_t address) noexcept;
	using WriteHandler = bool (*)(GameBoy &gameBoy, Data *data, uint16_t address, uint8_t value) noexcept;

	MemoryBankController() noexcept = default;

	Result<uint8_t> read(GameBoy &gameBoy, uint16_t address) const noexcept;
	bool write(GameBoy &gameBoy, uint16_t address, uint8_t value) const noexcept;

	static MemoryBankController CreateNone() noexcept;
	static MemoryBankController CreateMBC1() noexcept;
	static MemoryBankController CreateMBC2() noexcept;
	static MemoryBankController CreateMBC3() noexcept;
	static MemoryBankController CreateMBC3_RTC() noexcept;
	static MemoryBankController CreateMBC5() noexcept;

	using Creator = typeof(CreateNone);

private:
	MemoryBankController(ReadHandler readHandler, WriteHandler writeHandler) noexcept;
	MemoryBankController(ReadHandler readHandler, WriteHandler writeHandler, std::unique_ptr<Data> &&data) noexcept;

	ReadHandler m_readHandler = nullptr;
	WriteHandler m_writeHandler = nullptr;
	std::unique_ptr<Data> m_data = {};
};


#endif //XGBE_MEMORYBANKCONTROLLER_H
