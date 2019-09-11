set(files
        Cartridge/RealTimeClock.cpp

        Cpu/Instructions/CbInstruction.cpp
        Cpu/Instruction.cpp
        Cpu/InstructionTable.cpp
        Cpu/CbInstructionTable.cpp
        Cpu/Instructions.cpp
        Cpu/CpuRegisters.cpp
        Cpu/InterruptRegisters.cpp
        Cpu/InterruptController.cpp

        Memory/MBC1.cpp
        Memory/MBC2.cpp
        Memory/MBC3.cpp
        Memory/MBC3_RTC.cpp
        Memory/MBC5.cpp
        Memory/MBCNone.cpp
        Memory/MemoryBankController.cpp

        Arguments.cpp
        Bus.cpp
        Cartridge.cpp
        Clock.cpp
        Cpu.cpp
        Emulation.cpp
        GameBoy.cpp
        GameBoyLoader.cpp
        TimeController.cpp
        )

add_library(emulation ${files})

target_include_directories(emulation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
