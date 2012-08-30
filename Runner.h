/*
 * Runner.h
 *
 *  Created on: Aug 30, 2012
 *      Author: nazgee
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include <osock-1.0/osock.h>
#include <misc/Interruptible.h>
#include <list>

namespace ecce {
typedef std::shared_ptr<osock::Server>   ServerPtr;
typedef typename std::list<ServerPtr>::iterator ServerIterator;

class Runner : public Interruptible {
	std::list< ServerPtr > mHandlers;


public:
	Runner();
	virtual ~Runner();
	void run();

	void install(ServerPtr server) {
		mHandlers.push_back(server);
	}
};
}
#endif /* RUNNER_H_ */
