//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_INTERRUPTREGISTERS_H
#define XGBE_INTERRUPTREGISTERS_H

#include <cstdint>
#include <type_traits>

class InterruptRegisters {
public:
	enum Registers : uint8_t {
		IME = 0,
		IE,
		IF,

		RegistersSize
	};
	enum Interrupts {
		IMEBit = 0,
		VBlank = 0,
		LcdStat,
		Timer,
		Serial,
		Joypad,

		InterruptsSize
	};

	void reset() noexcept;

	template<Registers Idx>
	[[nodiscard]] inline uint8_t read() const noexcept { return m_registers[Idx]; }

	template<Registers Idx>
	inline void write(uint8_t value) noexcept { m_registers[Idx] = value; }

	template<Registers Idx>
	[[nodiscard]] inline uint8_t &ref() noexcept { return m_registers[Idx]; }

	template<Registers Idx, Interrupts Offset>
	inline void set() noexcept { m_registers[Idx] |= 1u << Offset; }

	template<Registers Idx>
	inline void set(uint8_t offset) noexcept { m_registers[Idx] |= 1u << offset; }

	template<Registers Idx, Interrupts Offset>
	inline void clear() noexcept { m_registers[Idx] &= ~(1u << Offset); }

	template<Registers Idx>
	inline void clear(uint8_t offset) noexcept { m_registers[Idx] &= ~(1u << offset); }

	template<Registers Idx, Interrupts Offset>
	inline bool get() noexcept { return m_registers[Idx] & (1u << Offset); }

	template<Registers Idx>
	inline bool get(uint8_t offset) noexcept { return m_registers[Idx] & (1u << offset); }

	inline uint8_t &operator[](Registers index) noexcept { return m_registers[index]; }
	inline const uint8_t &operator[](Registers index) const noexcept { return m_registers[index]; }

private:
	uint8_t m_registers[RegistersSize] = {};
};

#endif //XGBE_INTERRUPTREGISTERS_H
