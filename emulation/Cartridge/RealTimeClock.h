//
// Created by Revolware Company on 2019-09-10.
//

#ifndef XGBE_REALTIMECLOCK_H
#define XGBE_REALTIMECLOCK_H

#include <cstdint>

class GameBoy;

class RealTimeClock {
public:
	enum Registers {
		S = 0,
		M,
		H,
		DL,
		DH,

		RegistersSize
	};

	enum DHBit {
		DCMsb = 0,
		Halt = 6,
		DCCarry = 7
	};

	void advance(GameBoy &gameBoy, double time) noexcept;

	void reset() noexcept;

	template<Registers Idx>
	[[nodiscard]] inline uint8_t read() const noexcept { return m_registers[Idx]; }

	template<Registers Idx>
	inline void write(uint8_t value) noexcept { m_registers[Idx] = value; }

	template<Registers Idx>
	[[nodiscard]] inline uint8_t &ref() noexcept { return m_registers[Idx]; }

	template<Registers Idx, DHBit Offset>
	inline void set() noexcept { m_registers[Idx] |= 1u << Offset; }

	template<Registers Idx>
	inline void set(uint8_t offset) noexcept { m_registers[Idx] |= 1u << offset; }

	template<Registers Idx, DHBit Offset>
	inline void clear() noexcept { m_registers[Idx] &= ~(1u << Offset); }

	template<Registers Idx>
	inline void clear(uint8_t offset) noexcept { m_registers[Idx] &= ~(1u << offset); }

	template<Registers Idx, DHBit Offset>
	inline bool get() noexcept { return m_registers[Idx] & (1u << Offset); }

	template<Registers Idx>
	inline bool get(uint8_t offset) noexcept { return m_registers[Idx] & (1u << offset); }

	inline uint8_t &operator[](uint8_t index) noexcept { return m_registers[index]; }
	inline const uint8_t &operator[](uint8_t index) const noexcept { return m_registers[index]; }

private:
	void advance(GameBoy &gameBoy) noexcept;
	void advanceDH(GameBoy &gameBoy) noexcept;

	uint8_t m_registers[RegistersSize] = {};

	double m_secondsSinceLastUpdate = 0.0;
};


#endif //XGBE_REALTIMECLOCK_H
