/*
 * OS_program.c
 *
 *  Created on: Jul 14, 2019
 *      Author: osama
 */
#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MTIMER0_interface.h"
#include "OS_interface.h"
#include "OS_config.h"
#include "OS_private.h"

Task SysTasks[NUM_TASKS] = {0};

void OS_init(void) {
	MTIMER0_voidInit();
	MTIMER0_voidSetCallback(OS_scheduler, MTIMER0_U8_CALLBACK_OVERFLOW);
	MTIMER0_voidSetDesiredTimeMs(TICK_TIME_MS);
}

void OS_start(void) {
	MTIMER0_voidEnable();
}

void OS_scheduler(void) {
	uint32 i;
	for (i = 0; i < NUM_TASKS; i++) {
		SysTasks[i].firstDelay--;
		if (SysTasks[i].firstDelay == 0) {
			if (SysTasks[i].state == RUNNING) {
				SysTasks[i].taskHandler();
			}
			SysTasks[i].firstDelay = SysTasks[i].period;
		}
	}
}

uint8 OS_createTask(void (*ptr) (void), uint32 period, uint32 priority, uint32 firstDelay) {
	uint8 exitStatus = 0;
	if (priority <= NUM_TASKS) {
		if (SysTasks[priority].period == 0) {
			SysTasks[priority].taskHandler = ptr;
			SysTasks[priority].period = period;
			SysTasks[priority].firstDelay = firstDelay;
		} else {
			exitStatus = 1;
		}
	} else {
		exitStatus = 1;
	}
	return exitStatus;
}

uint8 OS_deleteTask(uint32 priority) {
	uint8 exitStatus = 0;
	if (priority < NUM_TASKS) {
		if (SysTasks[priority].period != 0) {
			SysTasks[priority].period = 0;
		} else {
			exitStatus = 1;
		}
	} else {
		exitStatus = 1;
	}
	return exitStatus;
}

uint8 OS_suspend(uint32 priority) {
	uint8 exitStatus = 0;
	if (priority < NUM_TASKS) {
		if (SysTasks[priority].period != 0 && SysTasks[priority].state == RUNNING) {
			SysTasks[priority].state = SUSPENDED;
		} else {
			exitStatus = 1;
		}
	} else {
		exitStatus = 1;
	}
	return exitStatus;
}

uint8 OS_resume(uint32 priority) {
	uint8 exitStatus = 0;
	if (priority < NUM_TASKS) {
		if (SysTasks[priority].period != 0 && SysTasks[priority].state == SUSPENDED) {
			SysTasks[priority].state = RUNNING;
		} else {
			exitStatus = 1;
		}
	} else {
		exitStatus = 1;
	}
	return exitStatus;
}
