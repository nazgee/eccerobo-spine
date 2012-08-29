/*
 * ExceptionModbus.h
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#ifndef MODBUSEXCEPTION_H_
#define MODBUSEXCEPTION_H_

#include <errno.h>
#include <stdexcept>

class ModbusException : public std::runtime_error {
public:
	int err;
	ModbusException(const std::string& arg) :
		std::runtime_error((arg + ": " ) + modbus_strerror(errno)) {
		err = errno;
	}

	int getErr() const {
		return err;
	}
};

#endif /* MODBUSEXCEPTION_H_ */
