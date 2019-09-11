//
// Created by Revolware Company on 2019-09-10.
//

#ifndef XGBE_TIMECONTROLLER_H
#define XGBE_TIMECONTROLLER_H

#include <cstdint>

class GameBoy;

namespace TimeController {
	void advanceTime(GameBoy &gameBoy, uint64_t clocks);
}


#endif //XGBE_TIMECONTROLLER_H
