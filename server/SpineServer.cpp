/*
 * SpineServer.cpp
 *
 *  Created on: Sep 1, 2012
 *      Author: nazgee
 */

#include "../modbus/Modbus.h"
#include "SpineServer.h"
#include "../misc/Logger.h"
#include "TokenizingException.h"
#include "HandlerModbus.h"

#include <boost/tokenizer.hpp>
#include <map>


namespace ecce {
static Logger logger("SpineServer");

SpineServer::SpineServer(std::shared_ptr<Modbus> modbus, osock::Auth_p auth, std::string portname, osock::Server::serviceType servicetype) :
	osock::Server(auth, portname, servicetype) {

	mHandler = Handler_p(new Handler());
	Handler_p getter = Handler_p(new Handler());
	Handler_p get_motor1 = Handler_p(new HandlerModbus(modbus, 499));
	Handler_p get_motor2 = Handler_p(new HandlerModbus(modbus, 500));

	Handler_p setter = Handler_p(new Handler());
	Handler_p set_motor1 = Handler_p(new HandlerModbus(modbus, 499, true));
	Handler_p set_motor2 = Handler_p(new HandlerModbus(modbus, 500, true));

	mHandler->install("get", getter);
	getter->install("motor1", get_motor1);
	getter->install("motor2", get_motor2);

	mHandler->install("set", setter);
	setter->install("motor1", set_motor1);
	setter->install("motor2", set_motor2);
}

SpineServer::~SpineServer() {

}

void SpineServer::Manage(osock::BIO_p bio) {
	osock::Parser parser(bio);

	osock::StringMessage msg("", osock::http::NEWLINE);

	while(1) {
		parser.Receive(msg);

		boost::tokenizer<> tok(msg);
		boost::tokenizer<>::iterator beg = tok.begin();

		if (beg == tok.end()) {
			throw TokenizingException("empty CMD");
		}

		parser.Send(*mHandler->handle("", beg).get());
	}

	NFO << "client is gone" << std::endl;
}

} /* namespace ecce */
