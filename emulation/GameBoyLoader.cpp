//
// Created by Revolware Company on 2019-09-07.
//

#include <fstream>
#include "GameBoyLoader.h"
#include "Arguments.h"

namespace GameBoyLoader {
	BiosRom::LoaderType loadBios()
	{
		std::fstream file(ApplicationConfig.biosPath, std::ios::binary | std::ios::in);

		if(!file.is_open())
			throw std::runtime_error(std::string("Failed to open bios file ") + ApplicationConfig.biosPath + "\n");


		auto loader = BiosRom::CreateLoader();
		file.read(BiosRom::GetLoader(loader), BiosRom::Size);

		return loader;
	}

	CartridgeRom::LoaderType loadRom()
	{
		std::fstream file(ApplicationConfig.romPath, std::ios::binary | std::ios::in);

		if(!file.is_open())
			throw std::runtime_error(std::string("Failed to open rom file ") + ApplicationConfig.romPath + "\n");


		auto loader = CartridgeRom::CreateLoader();

		file.seekg(0, std::ios::end);
		loader.resize(file.tellg());
		file.seekg(0, std::ios::beg);

		file.read(CartridgeRom::GetLoader(loader), loader.size());

		return loader;
	}

	GameBoy load()
	{
		return GameBoy(
				loadBios(),
				loadRom()
		);
	}
}
