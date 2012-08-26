/*
 * mb.h
 *
 *  Created on: Aug 26, 2012
 *      Author: nazgee
 */

#ifndef MB_H_
#define MB_H_

#include <cfg/SerialConfig.h>

#include <modbus/modbus.h>
#include <stdexcept>
#include <string>
#include <errno.h>

class ModbusException : public std::runtime_error {
public:
	int err;
	ModbusException(const std::string& arg) :
		std::runtime_error((arg + ": " ) + modbus_strerror(errno)) {
		err = errno;
	}
};

class Modbus {
private:
	modbus_t *ctx;
	static std::string toString(int addr, int nb, uint16_t* buff);
public:
	Modbus(SerialConfig config);
	~Modbus();
	void testrun();
	void readInputRegisters(int addr, int nb, uint16_t* buff);
	void readRegisters(int addr, int nb, uint16_t* buff);
	void writeRegisters(int addr, int nb, uint16_t* buff);
};


#endif /* MB_H_ */
