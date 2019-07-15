/*
 * OS_private.h
 *
 *  Created on: Jul 14, 2019
 *      Author: osama
 */

#ifndef OS_PRIVATE_H_
#define OS_PRIVATE_H_

typedef struct {
	void (*taskHandler) (void);
	uint32 period;
	uint32 firstDelay;
	uint8 state;
} Task;

enum States {RUNNING = 0, SUSPENDED};

#endif /* OS_PRIVATE_H_ */
