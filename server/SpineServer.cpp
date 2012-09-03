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
	Handler_p get_range = Handler_p(new HandlerFile("/dev/ultrasonic.0.hcsr04"));
	Handler_p get_servo = Handler_p(new HandlerFile("/dev/servodrive1"));

	Handler_p setter = Handler_p(new Handler());
	Handler_p set_motor1 = Handler_p(new HandlerModbus(modbus, 499, true));
	Handler_p set_motor2 = Handler_p(new HandlerModbus(modbus, 500, true));
	Handler_p set_servo = Handler_p(new HandlerFile("/dev/servodrive1", true));

	mHandler->install("get", getter);
	getter->install("motor1", get_motor1);
	getter->install("motor2", get_motor2);
	getter->install("range", get_range);
	getter->install("servo", get_servo);

	mHandler->install("set", setter);
	setter->install("motor1", set_motor1);
	setter->install("motor2", set_motor2);
	setter->install("servo", set_servo);

//	std::string s = "this is just a test, of -neg valuese -10\r\n";
//	tokenizer tokens(s, boost::char_separator<char>(" \r\n"));
//
//	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
//		std::cout << "<" << *tok_iter << "> ";
//	std::cout << "\n";
}

SpineServer::~SpineServer() {

}

void SpineServer::Manage(osock::BIO_p bio) {
	osock::Parser parser(bio);

	osock::StringMessage msg("", osock::http::NEWLINE);

	while(1) {
		parser.Receive(msg);

		tokenizer tokens(msg, boost::char_separator<char>(" \r\n"));
		tokenizer::iterator tok = tokens.begin();

		if (tok == tokens.end()) {
			throw TokenizingException("empty CMD");
		}

		parser.Send(*mHandler->handle("", tok).get());
	}

	NFO << "client is gone" << std::endl;
}

} /* namespace ecce */
