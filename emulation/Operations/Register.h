//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_REGISTER_OPERATIONS_H
#define XGBE_REGISTER_OPERATIONS_H

#include "GameBoy.h"

namespace RegisterOperations {
	inline uint8_t &refA(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().ref<CpuRegisters::A>(); }
}

#endif //XGBE_REGISTER_OPERATIONS_H
