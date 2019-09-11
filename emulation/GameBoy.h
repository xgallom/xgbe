//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_GAMEBOY_H
#define XGBE_GAMEBOY_H

#include "Bus.h"
#include "Cartridge.h"
#include "Cpu.h"
#include "Clock.h"
#include "Memory/BiosRom.h"
#include "Memory/HighRam.h"
#include "Memory/WorkRam.h"

#include <memory>

class GameBoy {
	static constexpr auto UninterruptedRunCyclesThreshold = 100;

public:
	explicit GameBoy(
			BiosRom::LoaderType &&biosLoader,
			CartridgeRom::LoaderType &&romLoader
	) noexcept;
	~GameBoy();

	void reset() noexcept;
	bool runCycles(GameBoy &gameBoy, uint64_t &cycles) noexcept;
	void runOnce(GameBoy &gameBoy) noexcept;

	[[nodiscard]] inline Bus &bus() noexcept { return m_bus; }
	[[nodiscard]] inline Cpu &cpu() noexcept { return m_cpu; }
	[[nodiscard]] inline Clock &clock() noexcept { return m_clock; }
	[[nodiscard]] inline Cartridge &cartridge() noexcept { return m_cartridge; }
	[[nodiscard]] inline HighRam &hram() noexcept { return m_highRam; }
	[[nodiscard]] inline WorkRam &wram() noexcept { return m_workRam; }
	[[nodiscard]] inline const BiosRom &bios() const noexcept { return m_bios; }

private:
	bool tryRunOnce(GameBoy &gameBoy, uint64_t &cycles) noexcept;

	uint64_t m_waitingCycles = 0;

	Bus m_bus = {};
	Cpu m_cpu = {};
	Clock m_clock = {};
	Cartridge m_cartridge;
	HighRam m_highRam;
	WorkRam m_workRam;
	const BiosRom m_bios;
};


#endif //XGBE_GAMEBOY_H
