//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_INSTRUCTION_H
#define XGBE_INSTRUCTION_H

#include <cstdint>
#include <limits>

class GameBoy;

class Instruction {
public:
	static constexpr uint64_t InvalidInstruction = std::numeric_limits<uint64_t>::max();
	using Handler = uint64_t (*)(GameBoy &gameBoy);

	explicit constexpr Instruction(Handler handler) noexcept : m_handler{handler} {}

	uint64_t execute(GameBoy &gameBoy) const noexcept;

private:
	Handler m_handler = {};
};

#endif //XGBE_INSTRUCTION_H
