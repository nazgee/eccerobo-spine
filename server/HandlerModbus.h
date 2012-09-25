/*
 * HandlerModbus.h
 *
 *  Created on: Sep 2, 2012
 *      Author: nazgee
 */

#ifndef HANDLERMODBUS_H_
#define HANDLERMODBUS_H_

#include "Handler.h"
#include "../modbus/Modbus.h"

#include <memory>

namespace ecce {

class HandlerModbus: public ecce::Handler {
	std::shared_ptr<Modbus> mModbus;
	int mModbusAddress;
public:
	HandlerModbus(std::shared_ptr<Modbus> modbus, int address);
	virtual ~HandlerModbus();
	std::shared_ptr<osock::Message> handle(
			const std::string& previous_token,
			const std::string& current_token,
			tokenizer::iterator &tok);
protected:
	void write(uint16_t value);
	uint16_t read();
};

} /* namespace ecce */
#endif /* HANDLERMODBUS_H_ */
