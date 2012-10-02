/*
 * Wheels.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: nazgee
 */


#include "Wheels.h"

namespace ecce {

#define SPEED_MAX 32767
#define SPEED_MIN 16535
#define LOOKUP_SIZE 9
#define SPEED_STEP ((SPEED_MAX-SPEED_MIN) / (LOOKUP_SIZE/2 - 1))

static int8_t lookup[][LOOKUP_SIZE] = {
//	L				C				R
	{0,	1,	2,	3,	4,	4,	4,	4,	4}, // 4
	{-1,	0,	1,	2,	3,	4,	4,	4,	4}, // 3
	{-2,	-1,	0,	1,	2,	3,	4,	4,	4}, // 2
	{-3,	-2,	-1,	0,	1,	2,	3,	4,	4}, // 1
	{-4,	-3,	-2,	-1,	0,	1,	2,	3,	4}, // 0
	{-4,	-4,	-3,	-2,	-1,	0,	1,	2,	3}, //-1
	{-4,	-4,	-4,	-3,	-2,	-1,	0,	1,	2}, //-2
	{-4,	-4,	-4,	-4,	-3,	-2,	-1,	0,	1}, //-3
	{-4,	-4,	-4,	-4,	-4,	-3,	-2,	-1,	0}  //-4
};

int8_t LOOKUP_Get(int8_t speed, int8_t turn, uint8_t translate) {
	// translate to array dimensions domain
	speed += LOOKUP_SIZE/2;
	turn += LOOKUP_SIZE/2;

	if(!translate) {
		return lookup[LOOKUP_SIZE - speed - 1][turn];
	} else {
		return lookup[turn][speed];
	}
}

int16_t LOOKUP_ToLateralSpeed(int16_t step) {
	if (step < 0) {
		return -SPEED_MIN + (step+1) * SPEED_STEP;
	} else if (step > 0) {
		return SPEED_MIN + (step-1) * SPEED_STEP;
	} else {
		return 0;
	}
}

int16_t LOOKUP_GetLateralSpeed(int8_t speed, int8_t turn, uint8_t right) {
	return LOOKUP_ToLateralSpeed(LOOKUP_Get(speed, turn, right));
}

Wheels::Wheels(std::shared_ptr<Modbus> modbus) :
		mModbus(modbus) {
	update(this->speed, this->turn);
}

Wheels::~Wheels() {

}

void Wheels::setSpeed(int8_t speed) {
	update(speed, this->turn);
	this->speed = speed;
}

void Wheels::setTurn(int8_t turn) {
	update(this->speed, turn);
	this->turn = turn;
}

void Wheels::update(int8_t speed, int8_t turn) {
	uint16_t regs[2];
	regs[0] = LOOKUP_GetLateralSpeed(speed, turn, 0); // left
	regs[1] = LOOKUP_GetLateralSpeed(speed, turn, 1); // right
	mModbus->writeRegisters(Modbus::eRegisters::REG_MOTORS_LEFT, 2, regs);
}

} /* namespace ecce */
