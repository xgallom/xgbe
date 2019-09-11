//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_ARGUMENTS_H
#define XGBE_ARGUMENTS_H

#include <string>

struct Arguments {
	static constexpr char
			DefaultBiosPath[] = "bios/boot.gbc";

	bool
			logDebug = false,
			windowed = false;

	const char *biosPath = DefaultBiosPath, *romPath = nullptr;

	static bool ParseIntoGlobal(int argc, char **argv) noexcept;
	static void PrintUsage() noexcept;
};

extern Arguments ApplicationConfig;

#endif //XGBE_ARGUMENTS_H
