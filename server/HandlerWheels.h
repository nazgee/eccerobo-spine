/*
 * HandlerWheels.h
 *
 *  Created on: Sep 25, 2012
 *      Author: nazgee
 */

#ifndef HANDLERWHEELS_H_
#define HANDLERWHEELS_H_

#include "HandlerModbus.h"
#include "Wheels.h"

namespace ecce {

class HandlerWheels: public ecce::Handler {
	Wheels mWheels;
public:
	static std::string TOKEN_TURN;
	static std::string TOKEN_SPEED;
	HandlerWheels(std::shared_ptr<Modbus> modbus);
	virtual ~HandlerWheels();

	std::shared_ptr<osock::Message> handle(
			const std::string& previous_token,
			const std::string& current_token,
			tokenizer::iterator &tok);
};

} /* namespace ecce */
#endif /* HANDLERWHEELS_H_ */
