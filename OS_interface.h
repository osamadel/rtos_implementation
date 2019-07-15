/*
 * OS_config.h
 *
 *  Created on: Jul 14, 2019
 *      Author: osama
 */

#ifndef OS_INTERFACE_H_
#define OS_INTERFACE_H_

void OS_init(void);
void OS_start(void);
void OS_scheduler(void);
uint8 OS_createTask(void (*ptr) (void), uint32 period, uint32 priority, uint32 firstDelay);
uint8 OS_deleteTask(uint32 priority);
uint8 OS_suspend(uint32 priority);
uint8 OS_resume(uint32 priority);

#endif /* OS_CONFIG_H_ */
