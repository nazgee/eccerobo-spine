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
	Handler_p get_motor = Handler_p(new HandlerModbus(modbus, 500));
	Handler_p get_range = Handler_p(new HandlerFile("/dev/ultrasonic.0.hcsr04"));
	Handler_p get_servo = Handler_p(new HandlerFile("/dev/servodrive1"));

	Handler_p setter = Handler_p(new Handler());
	Handler_p set_motor = Handler_p(new HandlerModbus(modbus, 500, true));
	Handler_p set_servo1 = Handler_p(new HandlerFile("/dev/servodrive1", true));
	Handler_p set_servo0 = Handler_p(new HandlerFile("/dev/servodrive0", true));

	mHandler->install("get", getter);
	getter->install("range", get_range);
	getter->install("engine", get_motor);
	getter->install("head", set_servo1);
	getter->install("turn", set_servo0);

	mHandler->install("set", setter);
	setter->install("engine", set_motor);
	setter->install("head", set_servo1);
	setter->install("turn", set_servo0);

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

		parser.Send(*mHandler->handle("", tok).get());
	}

	NFO << "client is gone" << std::endl;
}

} /* namespace ecce */
