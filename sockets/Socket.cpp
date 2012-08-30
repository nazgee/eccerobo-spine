/*
 * Channel.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <exceptions/SystemException.h>

Socket::Socket(std::string socketName) :
	mName(socketName) {
	register int len;
	struct sockaddr_un sockaddrunix;

	/*
	 * Get a socket to work with.  This socket will
	 * be in the UNIX domain, and will be a
	 * stream socket.
	 */
	if ((mAcceptSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		throw new SystemException("socket");
	}

	/*
	 * Create the address we will be binding to.
	 */
	sockaddrunix.sun_family = AF_UNIX;
	strcpy(sockaddrunix.sun_path, socketName.c_str());

	/*
	 * Make sure that socket name is not taken in an unfriendly way...
	 */
	unlink (socketName.c_str());

	/**
	 * Bind a socket with it's name
	 */
	len = sizeof(sockaddrunix.sun_family) + strlen(sockaddrunix.sun_path);
	if (bind(mAcceptSocket,(struct sockaddr *) &sockaddrunix, len) < 0) {
		throw new SystemException("bind");
	}

	/*
	 * Enable accepting connections
	 */
	if (listen(mAcceptSocket, 1) < 0) {
		throw new SystemException("listen");
	}
}

Socket::~Socket() {
	/*
	 * XXX: This is not needed... is it?
	 */
	unlink (getName().c_str());
}

int Socket::accept() {
	socklen_t len;
	int client;
	struct sockaddr_un client_addr;
	/*
	 * Accept connections.  When we accept one, ns
	 * will be connected to the client.  fsaun will
	 * contain the address of the client.
	 */
	if ((client = ::accept(mAcceptSocket, (struct sockaddr*)(&client_addr), &len)) < 0) {
		throw SystemException("accept");
	}

	return client;
}
