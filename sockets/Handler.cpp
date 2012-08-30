/*
 * Handler.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#include "Handler.h"

Handler::Handler(std::shared_ptr<Socket> socket) :
	mSocket(socket) {
}

Handler::Handler(std::string socketName) :
	mSocket(new Socket(socketName)) {
}

Handler::~Handler() {
}

void Handler::manage() {
	while (!isInterrupted()) {
		int client = mSocket->accept();
		handle(client);
	}
}

