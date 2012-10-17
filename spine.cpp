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

	std::shared_ptr<Modbus> modbus = std::shared_ptr<Modbus>(new Modbus(cfg.serial));

	// Prevent zombies creation
	osock::Server::InstallChildReaper();

	// Start server
	SpineServer server(modbus, osock::AuthNone::Populate(), cfg.getPort(), osock::Server::serviceType::serviceThread);
	server.Start();

	return EXIT_SUCCESS;
}
