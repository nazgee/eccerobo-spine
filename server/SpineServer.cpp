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
	mMapCmds["get"] = CMD_GET;
	mMapCmds["set"] = CMD_SET;

	mMapActors["motor1"] = ACTOR_MOTOR1;
	mMapActors["motor2"] = ACTOR_MOTOR2;
	mMapActors["servo"] = ACTOR_HEAD_SERVO;
	mMapActors["sensor"] = ACTOR_ULTRASONIC_SENSOR;

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
		//msg = mHandler->handle("", beg);

		parser.Send(*mHandler->handle("", beg).get());

//		// get CMD
//		if (beg == tok.end()) {
//			throw TokenizingException("empty CMD");
//		}
//		enum cmds cmd = mMapCmds[*beg];
//
//		// get ACTOR
//		++beg;
//		if (beg == tok.end()) {
//			throw TokenizingException("empty ACTOR");
//		}
//		std::string actor_string = *beg;
//		enum actors actor_cmd = mMapActors[*beg];
//
//		switch (cmd) {
//			case CMD_GET: {
//				switch (actor_cmd) {
//					case ACTOR_MOTOR1:
//					case ACTOR_MOTOR2: {
//						NFO << actor_string <<" "<< actor_cmd << std::endl;
//					} break;
//					case ACTOR_HEAD_SERVO: {
//						NFO << actor_string <<" "<< actor_cmd << std::endl;
//					} break;
//					case ACTOR_ULTRASONIC_SENSOR: {
//						NFO << actor_string <<" "<< actor_cmd << std::endl;
//					} break;
//					default: {
//						throw TokenizingException("unkown CMD");
//					} break;
//				}
//			} break;
//			case CMD_SET: {
//				// get VALUE
//				++beg;
//				if (beg == tok.end()) {
//					throw TokenizingException("empty VALUE");
//				}
//				std::string value_string = *beg;
//
//				switch (actor_cmd) {
//					case ACTOR_MOTOR1:
//					case ACTOR_MOTOR2: {
//						NFO << actor_string <<"->"<< value_string << std::endl;
//					} break;
//					case ACTOR_HEAD_SERVO: {
//						NFO << actor_string <<"->"<< value_string << std::endl;
//					} break;
//					case ACTOR_ULTRASONIC_SENSOR: {
//						NFO << actor_string <<"->"<< value_string << std::endl;
//					} break;
//					default: {
//						throw TokenizingException("unkown CMD");
//					} break;
//				}
//			} break;
//			default:
//				throw TokenizingException("unkown CMD");
//				break;
//		}
	}

	NFO << "client is gone" << std::endl;
}

} /* namespace ecce */
