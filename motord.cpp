//============================================================================
// Name        : motord.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include <memory>

#include <cfg/Config.h>
#include <modbus/Modbus.h>
#include <sockets/Server.h>
#include <EchoHandler.h>

int main(int argc, char **argv) {
	Config cfg(argc, argv);

	if (cfg.isVerbose()) {
		std::cout << "motord is starting..." << std::endl;
		std::cout << cfg.toString() << std::endl;
	}

//	Modbus mb(cfg.serial);
//	mb.testrun();

	Server srv;
	srv.install(std::shared_ptr<Handler>(new EchoHandler("/tmp/foo")));
	srv.run();

	return EXIT_SUCCESS;
}
