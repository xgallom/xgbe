//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_INTERRUPTCONTROLLER_H
#define XGBE_INTERRUPTCONTROLLER_H

#include <cstdint>

class GameBoy;

namespace InterruptController {
	static constexpr uint16_t InterruptVectorAddress = 0x0040, InterruptVectorOffset = 3;

	void handleInterrupts(GameBoy &gameBoy) noexcept;
}


#endif //XGBE_INTERRUPTCONTROLLER_H
