/*
 * Runner.cpp
 *
 *  Created on: Aug 30, 2012
 *      Author: nazgee
 */

#include "Runner.h"
#include <misc/Logger.h>
#include <exceptions/SystemException.h>

using namespace ecce;
static typename ecce::Logger logger("Runner");



Runner::Runner() {

}

Runner::~Runner() {
}

void Runner::run() {
	int pid = 0;

	ServerIterator ib = mHandlers.begin();
	ServerIterator ie = mHandlers.end();
	ServerPtr server;

	for (; ib != ie; ++ib) {
		server = *ib;

		/**
		 * Create child process for each handler
		 */
		pid = fork();
		if (pid < 0) {
			throw SystemException("fork");
		}

		if (pid == 0) {
			DBG << "@child; newborn " << getpid() << std::endl;
			break;
		} else {
			DBG << "@parent; forked new child" << std::endl;
		}
	}

	if (pid == 0) {
		// This is the child process
		server->Start();
		DBG << "@child; client handled " << getpid() << std::endl;
	} else {
		sleep(30);
		DBG << "@parent; finished sleeping" << std::endl;
	}
}
