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
#include <osock-1.0/osock.h>
#include <memory>
#include <signal.h>

#include "server/SpineServer.h"

using namespace ecce;


int main(int argc, char **argv) {
	Config cfg(argc, argv);

	if (cfg.isVerbose()) {
		std::cout << "eccerobo spine is starting..." << std::endl;
		std::cout << cfg.toString() << std::endl;
	}

	// Prevent zombies creation
	osock::Server::InstallChildReaper();
	SpineServer server = SpineServer(osock::AuthNone::Populate(), "10237");
	server.Start();

//	Modbus mb(cfg.serial);
//	mb.testrun();

	return EXIT_SUCCESS;
}
