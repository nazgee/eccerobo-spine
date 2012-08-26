//============================================================================
// Name        : motord.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>


#include <cfg/Config.h>
#include <modbus/Modbus.h>

int main(int argc, char **argv) {
	Config cfg(argc, argv);

	if (cfg.isVerbose()) {
		std::cout << "motord is starting..." << std::endl;
		std::cout << cfg.toString() << std::endl;
	}

	Modbus mb(cfg.serial);
	mb.testrun();

	return EXIT_SUCCESS;
}
