/*
 * Interruptible.h
 *
 *  Created on: Aug 30, 2012
 *      Author: nazgee
 */

#ifndef INTERRUPTIBLE_H_
#define INTERRUPTIBLE_H_

class Interruptible {
	bool mIsInterrupted;
public:
	Interruptible();
	virtual ~Interruptible();

	void interrupt() {
		mIsInterrupted = true;
	}

	bool isInterrupted() {
		return mIsInterrupted;
	}
};

#endif /* INTERRUPTIBLE_H_ */
