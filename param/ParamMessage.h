/*
 * ConfigMessage.h
 *
 *  Created on: Aug 31, 2012
 *      Author: nazgee
 */

#ifndef CONFIGMESSAGE_H_
#define CONFIGMESSAGE_H_

#include <osock-1.0/osock.h>

class ParamMessage: public osock::Message {
public:
	ParamMessage();
	virtual ~ParamMessage();
};

#endif /* CONFIGMESSAGE_H_ */
