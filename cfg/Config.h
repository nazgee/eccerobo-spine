/*
 * config.h
 *
 *  Created on: Aug 25, 2012
 *      Author: nazgee
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include "SerialConfig.h"

class Config {
public:
	Config(int argc, char **argv);
	SerialConfig serial;
	bool isVerbose() { return !mSilent; }
	std::string toString();

private:
	int mSilent;
};

#endif /* CONFIG_H_ */
