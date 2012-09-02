/*
 * SystemException.h
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#ifndef SYSTEMEXCEPTION_H_
#define SYSTEMEXCEPTION_H_

#include <errno.h>
#include <stdexcept>
#include <string.h>

class TokenizingException : public std::runtime_error {
public:
	TokenizingException(const std::string& arg) :
		std::runtime_error(arg) {
	}
};

#endif /* SYSTEMEXCEPTION_H_ */
