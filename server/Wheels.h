/*
 * Wheels.h
 *
 *  Created on: Sep 25, 2012
 *      Author: nazgee
 */

#ifndef WHEELS_H_
#define WHEELS_H_

#include <stdint.h>

namespace ecce {

class Wheels {
	int8_t speed;
	int8_t turn;
	std::shared_ptr<Modbus> mModbus;
	void update();
public:
	Wheels(std::shared_ptr<Modbus> modbus);
	virtual ~Wheels();

	void setSpeed(int8_t speed);
	void setTurn(int8_t turn);

	int8_t getSpeed() const {
		return speed;
	}
	int8_t getTurn() const {
		return turn;
	}
};

} /* namespace ecce */
#endif /* WHEELS_H_ */
