//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_CPU_REGISTERS_H
#define XGBE_CPU_REGISTERS_H

#include <cstdint>
#include <type_traits>

class CpuRegisters {
public:
	enum Word : uint8_t {
		AF = 0,
		BC,
		DE,
		HL,
		SP,
		PC,


		WordSize
	};

	enum Byte : uint8_t {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		F = 0, A,
		C, B,
		E, D,
		L, H,
		SL, SH,
		PL, PH,
#else
		A = 0, F,
		B, C,
		D, E,
		H, L,
		SH, SL,
		PH, PL,
#endif
		ByteSize
	};

	enum Flag : uint8_t {
		ZF = 7,
		NF = 6,
		HF = 5,
		CF = 4,

		FlagSize = 8
	};

	struct WordPair {
		uint16_t first, second;
	};

	void reset() noexcept;

	template<Byte Idx>
	[[nodiscard]] inline uint8_t read() const noexcept { return m_bytes[Idx]; }

	template<Byte Idx>
	inline void write(uint8_t value) noexcept { m_bytes[Idx] = value; }

	template<Byte Idx>
	[[nodiscard]] inline uint8_t &ref() noexcept { return m_bytes[Idx]; }

	template<Byte Idx>
	[[nodiscard]] inline uint8_t adv() noexcept { return ref<Idx>()++; }

	template<Word Idx>
	[[nodiscard]] inline uint16_t read() const noexcept { return m_words[Idx]; }

	template<Word Idx>
	inline void write(uint16_t value) noexcept { m_words[Idx] = value; }

	template<Word Idx>
	[[nodiscard]] inline uint16_t &ref() noexcept { return m_words[Idx]; }

	template<Word Idx>
	[[nodiscard]] inline uint16_t adv() noexcept { return ref<Idx>()++; }

	template<Word Idx>
	[[nodiscard]] inline uint16_t red() noexcept { return --ref<Idx>(); }

	template<Word Idx>
	[[nodiscard]] inline WordPair advTwo() noexcept
	{
		const auto first = adv<Idx>();
		return {first, adv<Idx>()};
	};

	template<Word Idx>
	[[nodiscard]] inline WordPair redTwo() noexcept
	{
		const auto second = red<Idx>();
		return {red<Idx>(), second};
	};

	template<Flag Idx>
	[[nodiscard]] inline bool read() const noexcept { return m_bytes[F] & (1u << Idx); }

	template<Flag Idx>
	inline void write(bool value) noexcept { if(value) set<Idx>(); else clear<Idx>(); }

	template<Flag Idx>
	inline void set() noexcept { m_bytes[F] |= 1u << Idx; }

	template<Flag Idx>
	inline void clear() noexcept { m_bytes[F] &= ~(1u << Idx); }

	inline uint16_t &operator[](Word index) noexcept { return m_words[index]; }
	inline const uint16_t &operator[](Word index) const noexcept { return m_words[index]; }

	inline uint8_t &operator[](Byte index) noexcept { return m_bytes[index]; }
	inline const uint8_t &operator[](Byte index) const noexcept { return m_bytes[index]; }

private:
	union {
		uint16_t m_words[WordSize] = {};
		uint8_t m_bytes[ByteSize];
	};
};

#endif //XGBE_CPU_REGISTERS_H
