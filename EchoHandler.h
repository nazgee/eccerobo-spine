/*
 * EchoHandler.h
 *
 *  Created on: Aug 30, 2012
 *      Author: nazgee
 */

#ifndef ECHOHANDLER_H_
#define ECHOHANDLER_H_

#include <sockets/Handler.h>

class EchoHandler: public Handler {
public:
	EchoHandler(std::string socketname);
	virtual ~EchoHandler();

	virtual void handle(int client);
};

#endif /* ECHOHANDLER_H_ */
