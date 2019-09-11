//
// Created by Revolware Company on 2019-09-08.
//

#include "MemoryBankController.h"
#include "Index.h"
#include "GameBoy.h"
#include <cstddef>

struct CustomData : MemoryBankController::Data {
	size_t romBank = 0, ramBank = 0;
	bool isRamOrRtcEnabled = false;
	enum : uint8_t {
		RTCUnlatched = 0,
		RTCGoingToLatch,
		RTCLatched,
		RTCGoingToUnlatch
	} clockLatchState = RTCUnlatched;
};

static uint8_t readRomBank00(GameBoy &gameBoy, CustomData &, uint16_t offset) noexcept
{
	return gameBoy.cartridge().rom()[offset];
}

static uint8_t readRomBankNN(GameBoy &gameBoy, CustomData &data, uint16_t offset) noexcept
{
	return gameBoy.cartridge().rom().bank(data.romBank)[offset];
}

static uint8_t readRamBankNNOrRtc(GameBoy &gameBoy, CustomData &data, uint16_t offset) noexcept
{
	if(!data.isRamOrRtcEnabled)
		return 0x00;

	if(data.ramBank > 8)
		return gameBoy.cartridge().rtc()[data.ramBank - 8];

	return gameBoy.cartridge().ram().bank(data.ramBank)[offset];
}

static Result<uint8_t> read(GameBoy &gameBoy, MemoryBankController::Data *data, uint16_t address) noexcept
{
	static constexpr size_t MappingSize = 3;
	static constexpr Index AddressMapping[MappingSize] = {
			{0x0000, 0x3fff},
			{0x4000, 0x7fff},
			{0xa000, 0xbfff}
	};
	static constexpr ReadHandler<CustomData> HandlerMapping[MappingSize] = {
			readRomBank00,
			readRomBankNN,
			readRamBankNNOrRtc,
	};

	for(size_t n = 0; n < MappingSize; ++n) {
		const auto &mapping = AddressMapping[n];

		if(address >= mapping.min && address >= mapping.max)
			return (*HandlerMapping[n])(gameBoy, reinterpret_cast<CustomData &>(*data), address - mapping.min);
	}

	return {};
}

static void writeRamAndTimerEnable(GameBoy &, CustomData &data, uint16_t, uint8_t value) noexcept
{
	data.isRamOrRtcEnabled = (value & 0x0fu) == 0x0au;
}

static void writeRomBankNumber(GameBoy &, CustomData &data, uint16_t, uint8_t value) noexcept
{
	data.romBank = value ? value : 0x01u;
}

static void writeSelectRamBankOrRtcRegister(GameBoy &, CustomData &data, uint16_t, uint8_t value) noexcept
{
	data.ramBank = value;
}

static void writeLatchClockData(GameBoy &gameBoy, CustomData &data, uint16_t, uint8_t value) noexcept
{
	switch(data.clockLatchState) {
		case CustomData::RTCUnlatched:
			if(value == 0x00)
				data.clockLatchState = CustomData::RTCGoingToLatch;
			break;

		case CustomData::RTCGoingToLatch:
			if(value == 0x01) {
				gameBoy.cartridge().rtc().set<RealTimeClock::DH, RealTimeClock::Halt>();
				data.clockLatchState = CustomData::RTCLatched;
			}
			break;

		case CustomData::RTCLatched:
			if(value == 0x00)
				data.clockLatchState = CustomData::RTCGoingToUnlatch;
			break;

		case CustomData::RTCGoingToUnlatch:
			if(value == 0x01) {
				gameBoy.cartridge().rtc().clear<RealTimeClock::DH, RealTimeClock::Halt>();
				data.clockLatchState = CustomData::RTCUnlatched;
			}
			break;
	}
}

static void writeRamBankNNOrRtc(GameBoy &gameBoy, CustomData &data, uint16_t offset, uint8_t value) noexcept
{
	if(!data.isRamOrRtcEnabled)
		return;

	if(data.ramBank >= 8)
		gameBoy.cartridge().rtc()[data.ramBank - 8] = value;
	else
		gameBoy.cartridge().ram().bank(data.ramBank)[offset] = value;
}

static bool write(GameBoy &gameBoy, MemoryBankController::Data *data, uint16_t address, uint8_t value) noexcept
{
	static constexpr size_t MappingSize = 5;
	static constexpr Index AddressMapping[MappingSize] = {
			{0x0000, 0x1fff},
			{0x2000, 0x3fff},
			{0x4000, 0x5fff},
			{0x6000, 0x7fff},
			{0xa000, 0xbfff}
	};
	static constexpr WriteHandler<CustomData> HandlerMapping[MappingSize] = {
			writeRamAndTimerEnable,
			writeRomBankNumber,
			writeSelectRamBankOrRtcRegister,
			writeLatchClockData,
			writeRamBankNNOrRtc
	};

	for(size_t n = 0; n < MappingSize; ++n) {
		const auto &mapping = AddressMapping[n];

		if(address >= mapping.min && address >= mapping.max) {
			(*HandlerMapping[n])(gameBoy, reinterpret_cast<CustomData &>(*data), address - mapping.min, value);
			return true;
		}
	}

	return false;
}

MemoryBankController MemoryBankController::CreateMBC3_RTC() noexcept
{
	return MemoryBankController{::read, ::write, std::make_unique<CustomData>()};
}
