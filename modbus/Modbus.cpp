/*
 * mb.cpp
 *
 *  Created on: Aug 26, 2012
 *      Author: nazgee
 */

#include "Modbus.h"
#include "../exceptions/ModbusException.h"

#include <stdio.h>
#include <stdlib.h>

namespace ecce {
Modbus::Modbus(SerialConfig config) {

	ctx = modbus_new_rtu(config.device.c_str(), config.baud_rate,
		(char)config.parity.get(), config.data_bits, config.stop_bits);

	if (!ctx) {
		throw ModbusException("modbus_new_rtu");
	}

//	modbus_flush(ctx);
//	modbus_set_debug(ctx, true);

	if (modbus_connect(ctx)) {
		throw ModbusException("modbus_connect");
	}

	if (modbus_set_slave(ctx, 10)) {
		throw ModbusException("modbus_set_slave");
	}

//	struct timeval response_timeout;
//	response_timeout.tv_sec = 1;
//	response_timeout.tv_usec = 500000;
//	modbus_set_response_timeout(ctx, &response_timeout);
//	modbus_set_byte_timeout(ctx, &response_timeout);

//	modbus_flush(ctx);
//
//	uint8_t *tab_bytes = NULL;
//	rc = modbus_report_slave_id(mb, tab_bytes);
//	if (rc > 1) {
//	    printf("Run Status Indicator: %s\n", tab_bytes[1] ? "ON" : "OFF");
//	}


}

Modbus::~Modbus() {
	modbus_close(ctx);
	modbus_free(ctx);
}
std::string Modbus::toString(int addr, int nb, uint16_t* buff) {
	std::stringstream ss;
	for (int i=0; i < nb; i++) {
		ss << "reg[" << i+addr <<"]=" << buff[i]
			<< " (0x" << std::hex << buff[i] << "); ";
	}
	return ss.str();
}
void Modbus::readInputRegisters(int addr, int nb, uint16_t* buff) {
	int rc = modbus_read_input_registers(ctx, addr, nb, buff);
	if (rc == -1) {
		throw ModbusException("modbus_read_input_registers");
	}
	std::cout << "read input: " << toString(addr, rc, buff) << std::endl;
}

void Modbus::readRegisters(int addr, int nb, uint16_t* buff) {
	int rc = modbus_read_registers(ctx, addr, nb, buff);
	if (rc == -1) {
		throw ModbusException("modbus_read_input_registers");
	}
	std::cout << "read: " << toString(addr, rc, buff) << std::endl;
}

void Modbus::writeRegisters(int addr, int nb, uint16_t* buff) {
	int rc = modbus_write_registers(ctx, addr, nb, buff);
	if (rc == -1) {
		throw ModbusException("modbus_write_registers");
	}
	std::cout << "write: " << toString(addr, rc, buff) << std::endl;
}
} // namespace ecce
