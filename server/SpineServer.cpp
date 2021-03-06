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
#include "HandlerFile.h"
#include "HandlerWheels.h"

#include <boost/tokenizer.hpp>
#include <map>


namespace ecce {
static Logger logger("SpineServer");

SpineServer::SpineServer(std::shared_ptr<Modbus> modbus, osock::Auth_p auth, std::string portname, osock::Server::serviceType servicetype) :
	osock::Server(auth, portname, servicetype) {

	mHandler = Handler_p(new Handler());
	Handler_p getter = Handler_p(new Handler());
	Handler_p setter = Handler_p(new Handler());
	Handler_p head = Handler_p(new HandlerFile("/dev/servodrive1"));
	Handler_p wheel = Handler_p(new HandlerWheels(modbus));

	mHandler->install(Handler::TOKEN_GET, getter);
	getter->install("range", Handler_p(new HandlerFile("/dev/ultrasonic.0.hcsr04")));
	getter->install(HandlerWheels::TOKEN_SPEED, wheel);
	getter->install(HandlerWheels::TOKEN_TURN, wheel);
	getter->install("head", head);

	mHandler->install(Handler::TOKEN_SET, setter);
	setter->install(HandlerWheels::TOKEN_SPEED, wheel);
	setter->install(HandlerWheels::TOKEN_TURN, wheel);
	setter->install("head", head);
}

SpineServer::~SpineServer() {

}



void SpineServer::Manage(osock::BIO_p bio) {
	osock::Parser parser(bio);
	osock::StringMessage msg("", osock::http::NEWLINE);

	NFO << "new client connected" << std::endl;

	boost::unique_lock<boost::mutex> lock(mSpineBusy, boost::try_to_lock);
	if (!lock.owns_lock()) {
		std::string s("ERR - spine in use!");
		msg.setString(s);
		parser.Send(msg);
		WRN << "spine is busy! killing off client connection" << std::endl;
		return;
	}

	NFO << "spine is taken over by new client" << std::endl;
	osock::BIOSocket* sock = (osock::BIOSocket*)bio.get();
	sock->setReadTimeout(5000);

	while(1) {
		parser.Receive(msg);
		tokenizer tokens(msg, boost::char_separator<char>(" \r\n"));
		tokenizer::iterator tok = tokens.begin();

		parser.Send(*mHandler->handle("", "", tok).get());
	}
}

} /* namespace ecce */
