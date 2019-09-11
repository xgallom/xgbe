//
// Created by Revolware Company on 2019-09-10.
//

#ifndef XGBE_INDEX_H
#define XGBE_INDEX_H

#include <cstdint>

class GameBoy;

struct Index {
	uint16_t min, max;
};

template<typename DataType>
using ReadHandler = uint8_t (*)(GameBoy &gameBoy, DataType &data, uint16_t offset) noexcept;
template<typename DataType>
using WriteHandler = void (*)(GameBoy &gameBoy, DataType &data, uint16_t offset, uint8_t value) noexcept;

#endif //XGBE_INDEX_H
