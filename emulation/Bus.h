//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_BUS_H
#define XGBE_BUS_H

#include <cstdint>
#include <cstddef>

class GameBoy;

class Bus {
public:
	using ReadHandler = uint8_t (Bus::*)(GameBoy &gameBoy, uint16_t offset) const noexcept;
	using WriteHandler = void (Bus::*)(GameBoy &gameBoy, uint16_t offset, uint8_t value) noexcept;

	void reset() noexcept;

	[[nodiscard]] uint8_t read(GameBoy &gameBoy, uint16_t address) const noexcept;
	void write(GameBoy &gameBoy, uint16_t address, uint8_t value) const noexcept;

private:
	uint8_t readVRam(GameBoy &gameBoy, uint16_t address) const noexcept;
	uint8_t readWRamBank00(GameBoy &gameBoy, uint16_t address) const noexcept;
	uint8_t readWRamBankNN(GameBoy &gameBoy, uint16_t address) const noexcept;
	uint8_t readEcho(GameBoy &gameBoy, uint16_t address) const noexcept;
	uint8_t readOAM(GameBoy &gameBoy, uint16_t address) const noexcept;
	uint8_t readIO(GameBoy &gameBoy, uint16_t address) const noexcept;
	uint8_t readHRam(GameBoy &gameBoy, uint16_t address) const noexcept;
	uint8_t readIE(GameBoy &gameBoy, uint16_t address) const noexcept;

	size_t m_vRamBank = 0, m_wRamBank = 0;
};


#endif //XGBE_BUS_H
