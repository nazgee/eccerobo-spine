/*
 * SpineServer.h
 *
 *  Created on: Sep 1, 2012
 *      Author: nazgee
 */

#ifndef SPINESERVER_H_
#define SPINESERVER_H_

#include <osock-1.0/osock.h>
#include "CompareString.h"
#include "Handler.h"

namespace ecce {

class SpineServer : public osock::Server {
	enum cmds {
		CMD_GET = 1,
		CMD_SET
	};
	std::map<std::string, enum cmds, CompareString> mMapCmds;

	enum actors {
		ACTOR_MOTOR1 = 1,
		ACTOR_MOTOR2,
		ACTOR_HEAD_SERVO,
		ACTOR_ULTRASONIC_SENSOR
	};
	std::map<std::string, enum actors, CompareString> mMapActors;

	Handler_p mHandler;
public:
	SpineServer(std::shared_ptr<Modbus> modbus, osock::Auth_p auth, std::string portname, osock::Server::serviceType servicetype = serviceCallback);
	virtual ~SpineServer();
	virtual void Manage(osock::BIO_p bio);
};

} /* namespace ecce */
#endif /* SPINESERVER_H_ */
