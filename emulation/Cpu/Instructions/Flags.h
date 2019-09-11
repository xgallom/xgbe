//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_FLAGS_H
#define XGBE_FLAGS_H

#include "GameBoy.h"
#include "Operands.h"

template<CpuRegisters::Flag Idx, bool Inv>
struct Flag {
};

template<CpuRegisters::Flag Idx>
struct Flag<Idx, false> {
	static constexpr auto Index = Idx;
	static constexpr auto Invert = false;
	static constexpr auto Type = OperandType::Flag;
	static constexpr auto Width = OperandWidth::Bit;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return gameBoy.cpu().registers().read<Index>(); }
};

template<CpuRegisters::Flag Idx>
struct Flag<Idx, true> {
	static constexpr auto Index = Idx;
	static constexpr auto Invert = true;
	static constexpr auto Type = OperandType::Flag;
	static constexpr auto Width = OperandWidth::Bit;

	using DataType = typename OperandWidth::Info<Width>::DataType;

	static inline DataType Read(GameBoy &gameBoy) noexcept { return !gameBoy.cpu().registers().read<Index>(); }
};

struct ZF : Flag<CpuRegisters::ZF, false> {
};
struct NZ : Flag<CpuRegisters::ZF, true> {
};
struct NF : Flag<CpuRegisters::NF, false> {
};
struct NN : Flag<CpuRegisters::NF, true> {
};
struct HF : Flag<CpuRegisters::HF, false> {
};
struct NH : Flag<CpuRegisters::HF, true> {
};
struct CF : Flag<CpuRegisters::CF, false> {
};
struct NC : Flag<CpuRegisters::CF, true> {
};

#endif //XGBE_FLAGS_H
