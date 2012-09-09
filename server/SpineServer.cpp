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
	Handler_p setter = Handler_p(new Handler());

	mHandler->install("get", getter);
	getter->install("range", Handler_p(new HandlerFile("/dev/ultrasonic.0.hcsr04")));
	getter->install("engine", Handler_p(new HandlerModbus(modbus, 500)));
	getter->install("head", Handler_p(new HandlerFile("/dev/servodrive1")));
	getter->install("turn", Handler_p(new HandlerFile("/dev/servodrive0")));

	mHandler->install("set", setter);
	setter->install("engine", Handler_p(new HandlerModbus(modbus, 500, true)));
	setter->install("head", Handler_p(new HandlerFile("/dev/servodrive1", true)));
	setter->install("turn", Handler_p(new HandlerFile("/dev/servodrive0", true)));

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
