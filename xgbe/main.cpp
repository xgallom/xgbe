#include <stdexcept>
#include <Log.h>
#include "Application.h"
#include "Arguments.h"

int main(int argc, char *argv[])
{
	if(!Arguments::ParseIntoGlobal(argc, argv)) {
		Arguments::PrintUsage();
		return 0;
	}

	Log::info("Rom:  ", ApplicationConfig.romPath, "\n");
	Log::info("Bios: ", ApplicationConfig.biosPath, "\n");

	try {
		Application application;
		application.run();
	} catch(const std::runtime_error &exception) {
		Log::error("Application ended with error code ", exception.what(), "\n");
	}

	return 0;
}