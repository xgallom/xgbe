//
// Created by Revolware Company on 2019-09-10.
//

#include "TimeController.h"
#include "GameBoy.h"

namespace TimeController {
	void advanceTime(GameBoy &gameBoy, uint64_t clocks)
	{
		const double time = clocks * gameBoy.clock().period();
		gameBoy.cartridge().rtc().advance(gameBoy, time);
	}
}
