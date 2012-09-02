/*
 * SpineServer.h
 *
 *  Created on: Sep 1, 2012
 *      Author: nazgee
 */

#ifndef SPINESERVER_H_
#define SPINESERVER_H_

#include <osock-1.0/osock.h>
#include "Handler.h"

namespace ecce {

class SpineServer : public osock::Server {
	Handler_p mHandler;
public:
	SpineServer(std::shared_ptr<Modbus> modbus, osock::Auth_p auth, std::string portname, osock::Server::serviceType servicetype = serviceCallback);
	virtual ~SpineServer();
	virtual void Manage(osock::BIO_p bio);
};

} /* namespace ecce */
#endif /* SPINESERVER_H_ */
