/*
 * Server.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#include "Server.h"
#include <misc/Logger.h>
#include <exceptions/SystemException.h>

static Logger logger("Server");

Server::Server() {
}

Server::~Server() {
}

void Server::run() {
	int pid = 0;

	HandlerIterator ib = mHandlers.begin();
	HandlerIterator ie = mHandlers.end();
	HandlerPtr handler;

	for (; ib != ie; ++ib) {
		handler = *ib;

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
		handler->manage();
		DBG << "@child; client handled " << getpid() << std::endl;
	} else {
		sleep(30);
		DBG << "@parent; finished sleeping" << std::endl;
	}
}

