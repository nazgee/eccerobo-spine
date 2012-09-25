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
#include <string>

namespace ecce {
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

	enum eRegisters {
		REG_MOTORS_LEFT = 499,
		REG_MOTORS_RIGHT = 500
	};
};
}

#endif /* MB_H_ */
