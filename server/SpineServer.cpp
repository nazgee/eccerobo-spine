/*
 * SpineServer.cpp
 *
 *  Created on: Sep 1, 2012
 *      Author: nazgee
 */

#include "SpineServer.h"
#include "../misc/Logger.h"
#include "TokenizingException.h"

#include <boost/tokenizer.hpp>
#include <map>


namespace ecce {
static Logger logger("SpineServer");

SpineServer::SpineServer(osock::Auth_p auth, std::string portname, osock::Server::serviceType servicetype) :
	osock::Server(auth, portname, servicetype) {
	mMapCmds["get"] = CMD_GET;
	mMapCmds["set"] = CMD_SET;

	mMapActors["motor1"] = ACTOR_MOTOR1;
	mMapActors["motor2"] = ACTOR_MOTOR2;
	mMapActors["servo"] = ACTOR_HEAD_SERVO;
	mMapActors["sensor"] = ACTOR_ULTRASONIC_SENSOR;
}

SpineServer::~SpineServer() {

}

void SpineServer::Manage(osock::BIO_p bio) {
	osock::Parser parse(bio);

	osock::StringMessage msg("", osock::http::NEWLINE);

	while(1) {
		parse.Receive(msg);
		parse.Send(msg);

		boost::tokenizer<> tok(msg);
		boost::tokenizer<>::iterator beg = tok.begin();

		// get CMD
		if (beg == tok.end()) {
			throw TokenizingException("empty CMD");
		}
		enum cmds cmd = mMapCmds[*beg];

		// get ACTOR
		++beg;
		if (beg == tok.end()) {
			throw TokenizingException("empty ACTOR");
		}
		std::string actor_string = *beg;
		enum actors actor_cmd = mMapActors[*beg];

		switch (cmd) {
			case CMD_GET: {
				switch (actor_cmd) {
					case ACTOR_MOTOR1:
					case ACTOR_MOTOR2: {
						NFO << actor_string <<" "<< actor_cmd << std::endl;
					} break;
					case ACTOR_HEAD_SERVO: {
						NFO << actor_string <<" "<< actor_cmd << std::endl;
					} break;
					case ACTOR_ULTRASONIC_SENSOR: {
						NFO << actor_string <<" "<< actor_cmd << std::endl;
					} break;
					default: {
						throw TokenizingException("unkown CMD");
					} break;
				}
			} break;
			case CMD_SET: {
				// get VALUE
				++beg;
				if (beg == tok.end()) {
					throw TokenizingException("empty VALUE");
				}
				std::string value_string = *beg;

				switch (actor_cmd) {
					case ACTOR_MOTOR1:
					case ACTOR_MOTOR2: {
						NFO << actor_string <<"->"<< value_string << std::endl;
					} break;
					case ACTOR_HEAD_SERVO: {
						NFO << actor_string <<"->"<< value_string << std::endl;
					} break;
					case ACTOR_ULTRASONIC_SENSOR: {
						NFO << actor_string <<"->"<< value_string << std::endl;
					} break;
					default: {
						throw TokenizingException("unkown CMD");
					} break;
				}
			} break;
			default:
				throw TokenizingException("unkown CMD");
				break;
		}
	}

	NFO << "client is gone" << std::endl;
}

} /* namespace ecce */
