/*
 * Server.h
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <misc/Interruptible.h>
#include <list>
#include <memory>

#include <sockets/Handler.h>

class Server : public Interruptible {
	std::list< std::shared_ptr<Handler> > mHandlers;

	typedef std::shared_ptr<Handler>   HandlerPtr;
	typedef typename std::list<HandlerPtr>::iterator HandlerIterator;

public:
	Server();
	virtual ~Server();
	void run();

	void install(std::shared_ptr<Handler> handler) {
		mHandlers.push_back(handler);
	}
};

#endif /* SERVER_H_ */
