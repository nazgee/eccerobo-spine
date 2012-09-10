/*
 * HandlerModbus.cpp
 *
 *  Created on: Sep 2, 2012
 *      Author: nazgee
 */

#include <sstream>
#include <boost/lexical_cast.hpp>

#include "TokenizingException.h"
#include "HandlerModbus.h"

namespace ecce {

HandlerModbus::HandlerModbus(std::shared_ptr<Modbus> modbus, int address, bool write) :
		mModbus(modbus),
		mModbusAddress(address),
		mWrite(write) {

}

HandlerModbus::~HandlerModbus() {
}

std::shared_ptr<osock::Message> HandlerModbus::handle(const std::string& current_token, tokenizer::iterator &tok) {

	uint16_t value;
	try {
		if (mWrite) {
			std::string token = getToken(tok);
			try {
				value = boost::lexical_cast<uint16_t>(token);
			} catch (boost::bad_lexical_cast e) {
				throw TokenizingException("bad param (" + token + " is not an int)");
			}
			write(value);
			return std::shared_ptr<osock::Message>(	new osock::StringMessage(REPLY_OK));
		} else {
			value = read();
			std::string res = REPLY_OK + " " + boost::lexical_cast<std::string>(value);
			return std::shared_ptr<osock::Message>(	new osock::StringMessage(res));
		}
	} catch (ModbusException e) {
		return std::shared_ptr<osock::Message>(	new osock::StringMessage(REPLY_ERR + " " + current_token + " " +  e.what()));
	}
}

void HandlerModbus::write(uint16_t value) {
	mModbus->writeRegisters(mModbusAddress, 1, &value);
}

uint16_t HandlerModbus::read() {
	uint16_t val;
	mModbus->readRegisters(mModbusAddress, 1, &val);
	return val;
}

} /* namespace ecce */
