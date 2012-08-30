/*
 * Handler.h
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#include <memory>
#include <sockets/Socket.h>
#include <misc/Interruptible.h>

class Handler : public Interruptible {

	std::shared_ptr<Socket> mSocket;
public:
	Handler(std::shared_ptr<Socket> socket);
	Handler(std::string socketName);
	virtual ~Handler();

	void manage();
	virtual void handle(int client) = 0;
};

#endif /* HANDLER_H_ */
