//
// Created by Revolware Company on 2019-09-07.
//

#include "Cartridge.h"
#include "Log.h"

Cartridge Cartridge::Create(CartridgeRom::LoaderType &&romLoader)
{
	size_t ramBanks = ramBanksFor(romLoader[0x0149]);

	switch(romLoader[0x0147]) {
		case Rom:
			ramBanks = RamNone;
		case Rom_Ram:
		case Rom_Ram_Battery:
			Log::info("Using no MBC\n");
			return Cartridge(MemoryBankController::CreateNone, std::move(romLoader), ramBanks * 8_kB);

		case MBC1:
			ramBanks = RamNone;
		case MBC1_Ram:
		case MBC1_Ram_Battery:
			Log::info("Using MBC1\n");
			return Cartridge(MemoryBankController::CreateMBC1, std::move(romLoader), ramBanks * 8_kB);

		case MBC2:
		case MBC2_Battery:
			ramBanks = RamNone;
			Log::info("Using MBC2\n");
			return Cartridge(MemoryBankController::CreateMBC2, std::move(romLoader), ramBanks * 8_kB);

		case MBC3_Timer_Battery:
			ramBanks = RamNone;
		case MBC3_Timer_Ram_Battery:
			Log::info("Using MBC3+RTC\n");

			if(ramBanks > Ram64k)
				throw std::runtime_error("Ram size exceeds allowed size for MBC3+RTC\n");

			return Cartridge(MemoryBankController::CreateMBC3_RTC, std::move(romLoader), ramBanks * 8_kB);

		case MBC3:
			ramBanks = RamNone;
		case MBC3_Ram:
		case MBC3_Ram_Battery:
			Log::info("Using MBC3\n");
			return Cartridge(MemoryBankController::CreateMBC3, std::move(romLoader), ramBanks * 8_kB);

		case MBC5:
		case MBC5_Rumble:
			ramBanks = RamNone;
		case MBC5_Ram:
		case MBC5_Ram_Battery:
		case MBC5_Rumble_Ram:
		case MBC5_Rumble_Ram_Battery:
			Log::info("Using MBC5\n");
			return Cartridge(MemoryBankController::CreateMBC5, std::move(romLoader), ramBanks * 8_kB);

		default:
			throw std::runtime_error("Invalid or unsupported cartridge type\n");
	}
}

size_t Cartridge::ramBanksFor(uint8_t ramSize) noexcept
{
	switch(ramSize) {
		case 0x01:
		case 0x02:
			return Ram8k;

		case 0x03:
			return Ram32k;

		case 0x04:
			return Ram128k;

		case 0x05:
			return Ram64k;

		default:
			return 0;
	}
}

Cartridge::Cartridge(
		MemoryBankController::Creator mbcCreator,
		CartridgeRom::LoaderType &&romLoader,
		size_t ramSize
) :
		m_memoryBankController(mbcCreator()),
		m_cartridgeRom(std::move(romLoader)),
		m_cartridgeRam(ramSize)
{
	Log::info("Ram size: ", ramSize / 1_kB, " kB\n");
}
