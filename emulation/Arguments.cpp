//
// Created by Revolware Company on 2019-09-07.
//

#include "Arguments.h"
#include <iostream>

bool Arguments::ParseIntoGlobal(int argc, char **argv) noexcept
{
	++argv;

	enum State {
		NoRom,
		NoBios,
		Full
	} state = NoRom;

	while(--argc) {
		const std::string argument = *argv;

		if(argument == "-D")
			ApplicationConfig.logDebug = true;
		else if(argument == "-W")
			ApplicationConfig.windowed = true;
		else {
			switch(state) {
				case NoRom:
					ApplicationConfig.romPath = *argv;
					state = NoBios;
					break;

				case NoBios:
					ApplicationConfig.biosPath = *argv;
					state = Full;
					break;

				case Full:
					return false;
			}
		}

		++argv;
	}

	return state != NoRom;
}

void Arguments::PrintUsage() noexcept
{
	std::cout
			<< "Invalid program arguments\n"
			<< "Usage: xgbe [-W|-D] rom_file_path [bios_file_path]\n";
}

Arguments ApplicationConfig = {};
