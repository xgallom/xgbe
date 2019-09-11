//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_MEMORY_H
#define XGBE_MEMORY_H

#include <cstdint>
#include <vector>

constexpr size_t operator ""_kB(unsigned long long size) noexcept { return size << 10; }

namespace MemoryAccess {
	enum Enum {
		RO = 0,
		RW
	};

	template<Enum Access>
	struct Info {
		using DataType = std::conditional_t<Access, uint8_t, const uint8_t>;
	};
}

template<size_t Sz, MemoryAccess::Enum Acc, size_t BkOff = 0>
class StaticMemory {
public:
	static constexpr auto Size = Sz;
	static constexpr auto Access = Acc;
	static constexpr auto BankOffset = BkOff;

	using DataType = typename MemoryAccess::Info<Access>::DataType;
	struct ArrayType {
		DataType data[Size];
	};
	struct LoaderArrayType {
		uint8_t data[Size];
	};
	using PointerType = std::unique_ptr<ArrayType>;
	using LoaderType = std::unique_ptr<LoaderArrayType>;

	StaticMemory() = default;
	explicit StaticMemory(PointerType &&data) : m_data(std::move(data)) {}
	explicit StaticMemory(LoaderType &&data) : m_data(reinterpret_cast<PointerType &&>(data)) {}

	static LoaderType CreateLoader() { return std::make_unique<LoaderArrayType>(); }
	static char *GetLoader(LoaderType &loader) noexcept { return reinterpret_cast<char *>(loader->data); }

	DataType *data() noexcept { return m_data->data; }
	const DataType *data() const noexcept { return m_data->data; }

	DataType *bank(size_t bank) noexcept { return m_data->data + (bank << BankOffset); }
	const DataType *bank(size_t bank) const noexcept { return m_data->data + (bank << BankOffset); }

	[[nodiscard]] size_t size() const noexcept { return Size; }

	DataType &operator[](uint16_t address) noexcept { return m_data->data[address]; }
	const DataType &operator[](uint16_t address) const noexcept { return m_data->data[address]; }

private:
	const PointerType m_data = std::make_unique<ArrayType>();
};

template<MemoryAccess::Enum Acc, size_t BkOff = 0>
class VariableMemory {
public:
	static constexpr auto Access = Acc;
	static constexpr auto BankOffset = BkOff;

	using DataType = typename MemoryAccess::Info<Access>::DataType;
	using ArrayType = DataType *;
	using LoaderArrayType = uint8_t *;
	using PointerType = std::vector<uint8_t>;
	using LoaderType = PointerType;

	VariableMemory() noexcept = default;
	explicit VariableMemory(size_t size) : m_data(size) {}
	explicit VariableMemory(PointerType &&data) : m_data(std::move(data)) {}

	static LoaderType CreateLoader(size_t initialSize = 0) { return LoaderType(initialSize); }
	static char *GetLoader(LoaderType &loader) noexcept { return reinterpret_cast<char *>(loader.data()); }

	DataType *data() noexcept { return m_data.data(); }
	const DataType *data() const noexcept { return m_data.data(); }

	DataType *bank(size_t bank) noexcept { return m_data.data() + (bank << BankOffset); }
	const DataType *bank(size_t bank) const noexcept { return m_data.data() + (bank << BankOffset); }

	[[nodiscard]] size_t size() const noexcept { return m_data.size(); }

	DataType &operator[](uint16_t address) noexcept { return m_data[address]; }
	const DataType &operator[](uint16_t address) const noexcept { return m_data[address]; }

private:
	std::conditional_t<std::is_const_v<DataType>, const PointerType, PointerType> m_data = {};
};

constexpr size_t RomBankOffset = 14;
template<size_t Sz, size_t BkOff = RomBankOffset>
using StaticRom = StaticMemory<Sz, MemoryAccess::RO, BkOff>;
template<size_t BkOff = RomBankOffset>
using Rom = VariableMemory<MemoryAccess::RO, BkOff>;

constexpr size_t RamBankOffset = 13;
template<size_t Sz, size_t BkOff = RamBankOffset>
using StaticRam = StaticMemory<Sz, MemoryAccess::RW, BkOff>;
template<size_t BkOff = RamBankOffset>
using Ram = VariableMemory<MemoryAccess::RW, BkOff>;

#endif //XGBE_MEMORY_H
