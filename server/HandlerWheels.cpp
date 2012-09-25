/*
 * HandlerWheels.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: nazgee
 */
#include <boost/lexical_cast.hpp>

#include "HandlerWheels.h"
#include "TokenizingException.h"
#include "../exceptions/ModbusException.h"

namespace ecce {

std::string HandlerWheels::TOKEN_SPEED = "speed";
std::string HandlerWheels::TOKEN_TURN = "turn";

HandlerWheels::HandlerWheels(std::shared_ptr<Modbus> modbus) :
		mWheels(modbus) {

}

HandlerWheels::~HandlerWheels() {

}

std::shared_ptr<osock::Message> HandlerWheels::handle(const std::string& previous_token, const std::string& current_token, tokenizer::iterator &tok) {

	int16_t value;
	try {
		if (previous_token == TOKEN_SET) {
			std::string token = getToken(tok);
			try {
				value = boost::lexical_cast<int16_t>(token);
			} catch (boost::bad_lexical_cast e) {
				throw TokenizingException("bad param (" + token + " is not an int16_t)");
			}

			if (current_token == TOKEN_SPEED) {
				mWheels.setSpeed(value);
			} else {
				mWheels.setTurn(value);
			}

			return std::shared_ptr<osock::Message>(	new osock::StringMessage(REPLY_OK));
		} else {
			if (current_token == TOKEN_SPEED) {
				value = mWheels.getSpeed();
			} else {
				value = mWheels.getTurn();
			}

			std::string res = REPLY_OK + " " + boost::lexical_cast<std::string>(value);
			return std::shared_ptr<osock::Message>(	new osock::StringMessage(res));
		}
	} catch (ModbusException& e) {
		return std::shared_ptr<osock::Message>(	new osock::StringMessage(REPLY_ERR + " " + current_token + " " +  e.what()));
	}
}

} /* namespace ecce */
