//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_OPERANDS_H
#define XGBE_OPERANDS_H

#include <Operations/Pc.h>
#include <Operations/Bus.h>
#include "GameBoy.h"
#include <type_traits>

template<bool Condition>
using EnableIf = std::enable_if_t<Condition, bool>;

namespace OperandType {
	enum Enum {
		Value,
		Register,
		Flag
	};
}

namespace OperandWidth {
	enum Enum {
		Byte,
		Word,
		Bit
	};

	template<Enum W>
	struct Info {
		static constexpr auto Width = W;
		using DataType = std::conditional_t<Width == OperandWidth::Word, uint16_t,
				std::conditional_t<Width == OperandWidth::Byte, uint8_t, bool>
		>;
	};
}

template<CpuRegisters::Byte Idx>
struct ByteReg {
	static constexpr auto Index = Idx;
	static constexpr auto Type = OperandType::Register;
	static constexpr auto Width = OperandWidth::Byte;
	static constexpr auto Writable = true;
	static constexpr auto Refable = true;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().read<Index>(); }
	static inline void Write(GameBoy &gameBoy, DataType value) noexcept
	{
		gameBoy.cpu().registers().write<Index>(value);
	}
	static inline DataType &Ref(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().ref<Index>(); }
};
template<CpuRegisters::Word Idx>
struct WordReg {
	static constexpr auto Index = Idx;
	static constexpr auto Type = OperandType::Register;
	static constexpr auto Width = OperandWidth::Word;
	static constexpr auto Writable = true;
	static constexpr auto Refable = true;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().read<Index>(); }
	static inline void Write(GameBoy &gameBoy, DataType value) noexcept
	{
		gameBoy.cpu().registers().write<Index>(value);
	}
	static inline DataType &Ref(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().ref<Index>(); }
};

struct A : ByteReg<CpuRegisters::A> {
};
struct B : ByteReg<CpuRegisters::B> {
};
struct C : ByteReg<CpuRegisters::C> {
};
struct D : ByteReg<CpuRegisters::D> {
};
struct E : ByteReg<CpuRegisters::E> {
};
struct F : ByteReg<CpuRegisters::F> {
};
struct H : ByteReg<CpuRegisters::H> {
};
struct L : ByteReg<CpuRegisters::L> {
};

struct AF : WordReg<CpuRegisters::AF> {
};
struct BC : WordReg<CpuRegisters::BC> {
};
struct DE : WordReg<CpuRegisters::DE> {
};
struct HL : WordReg<CpuRegisters::HL> {
};
struct SP : WordReg<CpuRegisters::SP> {
};
struct PC : WordReg<CpuRegisters::PC> {
};

struct D8 {
	static constexpr auto Type = OperandType::Value;
	static constexpr auto Width = OperandWidth::Byte;
	static constexpr auto Writable = false;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return PcOperations::loadByte(gameBoy); }
};

struct D16 {
	static constexpr auto Type = OperandType::Value;
	static constexpr auto Width = OperandWidth::Word;
	static constexpr auto Writable = false;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return PcOperations::loadWord(gameBoy); }
};

struct R8 {
	static constexpr auto Type = OperandType::Value;
	static constexpr auto Width = OperandWidth::Word;
	static constexpr auto Writable = false;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept
	{
		const auto base = PcOperations::read(gameBoy);
		return base + int16_t(PcOperations::loadWord(gameBoy));
	}
};

template<typename From>
struct IND {
	static_assert(From::Width == OperandWidth::Word, "Indirect operand must be 16-bit wide");

	static constexpr auto Type = From::Type;
	static constexpr auto Width = OperandWidth::Byte;
	static constexpr auto Writable = true;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept
	{
		return BusOperations::readByte(gameBoy, From::Read(gameBoy));
	}
	static inline void Write(GameBoy &gameBoy, DataType value) noexcept
	{
		BusOperations::writeByte(gameBoy, From::Read(gameBoy), value);
	}
};

template<typename From>
struct INDB {
	static_assert(From::Width == OperandWidth::Byte, "Indirect operand must be 8-bit wide");

	static constexpr auto Type = From::Type;
	static constexpr auto Width = OperandWidth::Byte;
	static constexpr auto Writable = true;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept
	{
		return BusOperations::readByte(gameBoy, Address(gameBoy));
	}
	static inline void Write(GameBoy &gameBoy, DataType value) noexcept
	{
		BusOperations::writeByte(gameBoy, From::Read(gameBoy), value);
	}

private:
	static inline uint16_t Address(GameBoy &gameBoy) noexcept { return 0xff00u + From::Read(gameBoy); }
};

template<typename From>
struct INDW {
	static_assert(From::Width == OperandWidth::Word, "Indirect operand must be 16-bit wide");

	static constexpr auto Type = From::Type;
	static constexpr auto Width = OperandWidth::Word;
	static constexpr auto Writable = true;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept
	{
		return BusOperations::readWord(gameBoy, From::Read(gameBoy));
	}
	static inline void Write(GameBoy &gameBoy, DataType value) noexcept
	{
		BusOperations::writeWord(gameBoy, From::Read(gameBoy), value);
	}
};

template<typename From>
struct PP {
	static_assert(From::Refable == true, "Increment operand must be referencable");

	static constexpr auto Type = From::Type;
	static constexpr auto Width = From::Width;
	static constexpr auto Writable = false;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return From::Ref(gameBoy)++; }
};

template<typename From>
struct MM {
	static_assert(From::Refable == true, "Decrement operand must be referencable");

	static constexpr auto Type = From::Type;
	static constexpr auto Width = From::Width;
	static constexpr auto Writable = false;
	static constexpr auto Refable = false;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return From::Ref(gameBoy)--; }
};

using A8 = INDB<D8>;

using A16 = IND<D16>;
using wA16 = INDW<D16>;

using HLI = PP<HL>;
using HLD = MM<HL>;

template<typename T>
static constexpr bool isByte() noexcept { return T::Width == OperandWidth::Byte; }
template<typename T>
static constexpr bool isWord() noexcept { return T::Width == OperandWidth::Word; }

template<typename T>
static constexpr bool isBit() noexcept { return T::Width == OperandWidth::Bit; }

#endif //XGBE_OPERANDS_H
