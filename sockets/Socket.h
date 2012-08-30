/*
 * Channel.h
 *
 *  Created on: Aug 29, 2012
 *      Author: nazgee
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
class Socket {
	std::string mName;
	int mAcceptSocket;
public:
	Socket(std::string socketName);
	virtual ~Socket();
	int accept();

	std::string getName() const {
		return mName;
	}
};

#endif /* CHANNEL_H_ */
