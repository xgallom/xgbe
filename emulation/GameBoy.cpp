//
// Created by Revolware Company on 2019-09-05.
//

#include "GameBoy.h"
#include "TimeController.h"
#include "Bus.h"

GameBoy::GameBoy(
		BiosRom::LoaderType &&biosData,
		CartridgeRom::LoaderType &&romLoader
) noexcept :
		m_cartridge{Cartridge::Create(std::move(romLoader))},
		m_bios{std::move(biosData)} {}

GameBoy::~GameBoy() = default;

void GameBoy::reset() noexcept
{
	m_waitingCycles = 0;

	cpu().reset();
	bus().reset();
	clock().reset();
}

bool GameBoy::runCycles(GameBoy &gameBoy, uint64_t &cycles) noexcept
{
	while(cycles > UninterruptedRunCyclesThreshold) {
		if(!tryRunOnce(gameBoy, cycles))
			return false;
	}

	return tryRunOnce(gameBoy, cycles);
}

void GameBoy::runOnce(GameBoy &gameBoy) noexcept
{
	TimeController::advanceTime(gameBoy, m_waitingCycles);
	m_waitingCycles = m_cpu.runOnce(gameBoy);
	InterruptController::handleInterrupts(gameBoy);
}

bool GameBoy::tryRunOnce(GameBoy &gameBoy, uint64_t &cycles) noexcept
{
	if(cycles > m_waitingCycles) {
		cycles -= m_waitingCycles;

		runOnce(gameBoy);

		return true;
	}

	return false;
}
