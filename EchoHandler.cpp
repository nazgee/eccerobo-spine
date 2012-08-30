/*
 * EchoHandler.cpp
 *
 *  Created on: Aug 30, 2012
 *      Author: nazgee
 */

#include <misc/Logger.h>
#include <exceptions/SystemException.h>
#include "EchoHandler.h"
#include <sys/socket.h>

static Logger logger("EchoHandler");

EchoHandler::EchoHandler(std::string socketname) :
	Handler(socketname) {
	// TODO Auto-generated constructor stub

}

EchoHandler::~EchoHandler() {
	// TODO Auto-generated destructor stub
}

void EchoHandler::handle(int client) {
	char buffer[100];
	while (!isInterrupted()) {
		int size = recv(client, buffer, sizeof buffer, 0);

		if (size >0) {
			std::string msg(buffer, size);
			DBG << "rxed: " << msg << std::endl;
			send(client, buffer, size, 0);
		} else {
			throw SystemException("recv");
		}
	}
}
