//
// Created by Revolware Company on 2019-09-05.
//

#include <Memory/Index.h>
#include "Bus.h"
#include "GameBoy.h"
#include "Log.h"

void Bus::reset() noexcept
{

}

uint8_t Bus::readVRam(GameBoy &gameBoy, uint16_t) const noexcept
{
	return 0x00; // TODO
}

uint8_t Bus::readWRamBank00(GameBoy &gameBoy, uint16_t offset) const noexcept
{
	return gameBoy.wram()[offset];
}

uint8_t Bus::readWRamBankNN(GameBoy &gameBoy, uint16_t offset) const noexcept
{
	return gameBoy.wram().bank(m_wRamBank)[offset];
}

uint8_t Bus::readEcho(GameBoy &gameBoy, uint16_t offset) const noexcept
{
	return read(gameBoy, 0xc000 + offset);
}

uint8_t Bus::readOAM(GameBoy &gameBoy, uint16_t) const noexcept
{
	return 0x00; // TODO
}

uint8_t Bus::readIO(GameBoy &gameBoy, uint16_t) const noexcept
{
	return 0x00; // TODO
}

uint8_t Bus::readHRam(GameBoy &gameBoy, uint16_t offset) const noexcept
{
	return gameBoy.hram()[offset];
}

uint8_t Bus::readIE(GameBoy &gameBoy, uint16_t) const noexcept
{
	return gameBoy.cpu().interruptRegisters().read<InterruptRegisters::IE>();
}

uint8_t Bus::read(GameBoy &gameBoy, uint16_t address) const noexcept
{
	static constexpr size_t MappingSize = 8;
	static constexpr Index AddressMapping[MappingSize] = {
			{0x8000, 0x9fff},
			{0xc000, 0xcfff},
			{0xd000, 0xdfff},
			{0xe000, 0xfdff},
			{0xfe00, 0xfe9f},
			{0xff00, 0xff7f},
			{0xff80, 0xffef},
			{0xffff, 0xffff}
	};
	static constexpr ReadHandler HandlerMapping[MappingSize] = {
			&Bus::readVRam,
			&Bus::readWRamBank00,
			&Bus::readWRamBankNN,
			&Bus::readEcho,
			&Bus::readOAM,
			&Bus::readIO,
			&Bus::readHRam,
			&Bus::readIE
	};

	Log::info("Read from ", address, "\n");

	const auto mbcResult = gameBoy.cartridge().mbc().read(gameBoy, address);

	if(mbcResult)
		return mbcResult();

	for(size_t n = 0; n < MappingSize; ++n) {
		const auto &mapping = AddressMapping[n];

		if(address >= mapping.min && address <= mapping.max)
			return (this->*HandlerMapping[n])(gameBoy, address - mapping.min);
	}

	Log::error("Invalid read from address ", address);
	return 0x00;
}

void Bus::write(GameBoy &gameBoy, uint16_t address, uint8_t value) const noexcept
{
	Log::info("Write to ", address, " <= ", value, "\n");

	if(gameBoy.cartridge().mbc().write(gameBoy, address, value))
		return;

	// TODO
}
