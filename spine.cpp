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
#include <osock-1.0/osock.h>
#include <Runner.h>
#include <memory>

using namespace ecce;
int main(int argc, char **argv) {
	Config cfg(argc, argv);

	if (cfg.isVerbose()) {
		std::cout << "eccerobo spine is starting..." << std::endl;
		std::cout << cfg.toString() << std::endl;
	}

	ServerPtr srv1 = ServerPtr(new osock::ServerEcho(osock::AuthNone::Populate(), "10237"));
//	ServerPtr srv2 = ServerPtr(new osock::ServerEcho(osock::AuthNone::Populate(), "10238"));
//	ServerPtr srv3 = ServerPtr(new osock::ServerEcho(osock::AuthNone::Populate(), "10239"));

	Runner runner;
	runner.install(srv1);
//	runner.install(srv2);
//	runner.install(srv3);

	runner.run();

//	Modbus mb(cfg.serial);
//	mb.testrun();

	return EXIT_SUCCESS;
}
