//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_CARTRIDGE_H
#define XGBE_CARTRIDGE_H

#include "Memory/MemoryBankController.h"
#include "Memory/CartridgeRom.h"
#include "Memory/CartridgeRam.h"
#include "Cartridge/RealTimeClock.h"

class Cartridge {
public:
	enum CartridgeType : uint8_t {
		Rom = 0x00,
		MBC1,
		MBC1_Ram,
		MBC1_Ram_Battery,

		MBC2 = 0x05,
		MBC2_Battery,

		Rom_Ram = 0x08,
		Rom_Ram_Battery,

		MMM01 = 0x0b,
		MMM01_Ram,
		MMM01_Ram_Battery,

		MBC3_Timer_Battery = 0x0f,
		MBC3_Timer_Ram_Battery,
		MBC3,
		MBC3_Ram,
		MBC3_Ram_Battery,

		MBC5 = 0x19,
		MBC5_Ram,
		MBC5_Ram_Battery,
		MBC5_Rumble,
		MBC5_Rumble_Ram,
		MBC5_Rumble_Ram_Battery,
		MBC6,
		MBC7_Sensor_Rumble_Ram_Battery,

		PocketCamera = 0xfc,
		BandaiTama5,
		HuC3,
		HuC1_Ram_Battery
	};

	enum RamSize : size_t {
		RamNone = 0,
		Ram8k = 1,
		Ram32k = 4,
		Ram128k = 16,
		Ram64k = 8
	};

	static Cartridge Create(CartridgeRom::LoaderType &&romLoader);

	[[nodiscard]] inline const MemoryBankController &mbc() const noexcept { return m_memoryBankController; }
	[[nodiscard]] inline const CartridgeRom &rom() const noexcept { return m_cartridgeRom; }
	[[nodiscard]] inline RealTimeClock &rtc() noexcept { return m_realTimeClock; }
	[[nodiscard]] inline CartridgeRam &ram() noexcept { return m_cartridgeRam; }

private:
	static size_t ramBanksFor(uint8_t ramSize) noexcept;

	Cartridge(
			MemoryBankController::Creator mbcCreator,
			CartridgeRom::LoaderType &&romLoader,
			size_t ramSize
	);

	const MemoryBankController m_memoryBankController;
	const CartridgeRom m_cartridgeRom;
	RealTimeClock m_realTimeClock;
	CartridgeRam m_cartridgeRam;
};

#endif //XGBE_CARTRIDGE_H
