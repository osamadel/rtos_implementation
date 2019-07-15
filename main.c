#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MDIO_interface.h"
#include "H7Segments_interface.h"
#include "HLCD_interface.h"
#include "MTIMER1_interface.h"
#include "OS_interface.h"
#include <util/delay.h>

/*Tick time every 50ms*/

void seg7(void) {
	/*every 2 ticks*/
	static uint8 seg7counter = 0;
	H7Seg_display(seg7counter);
	if (seg7counter < 9) seg7counter++;
	else seg7counter = 0;
}

void buzzer(void) {
	/*every 20 ticks*/
	static uint8 buzzerOn = 1;
	if (buzzerOn == 1) {
		MDIO_SetPinOutput(PORTA, 5, HIGH);
		buzzerOn = 0;
	} else {
		MDIO_SetPinOutput(PORTA, 5, LOW);
		buzzerOn = 1;
	}
}

void LCD(void) {
	/*every 5 ticks*/
	static uint8 shiftCount = 0;
	shiftCount++;
	if (shiftCount < 20)
		HLCD_shiftDisplay(SHIFT_RIGHT);
	else if (shiftCount < 40)
		HLCD_shiftDisplay(SHIFT_LEFT);
	else
		shiftCount = 0;
}

void servo(void) {
	static uint8 angle = 0;
	MTIMER1_voidSetPWM(angle);
	if (angle <= 160) angle += 10;
	else angle = 0;
}

void blink(void) {
	static uint8 ledOn = 1;
	if (ledOn == 1) {
		MDIO_SetPinOutput(PORTD, 0, HIGH);
		ledOn = 0;
	} else {
		MDIO_SetPinOutput(PORTD, 0, LOW);
		ledOn = 1;
	}
}

int main(void) {
	/*initialize DIO*/
	H7Seg_initialize();
	MTIMER1_voidInit();
	MTIMER1_voidEnable();
	HLCD_init(HLCD_4_BIT);
	HLCD_writeText("Osama");
	MDIO_SetPinDirection(PORTA, 5, OUTPUT);
	MDIO_SetPinDirection(PORTD, 5, OUTPUT);
	MDIO_SetPinDirection(PORTD, 0, OUTPUT);
	OS_init();

	/*Task creation*/
	OS_createTask(seg7, 10, 0, 1);
	OS_createTask(buzzer, 20, 1, 1);
	OS_createTask(LCD, 5, 2, 1);
	OS_createTask(servo, 8, 3, 1);
	OS_createTask(blink, 12, 4, 1);


	/*OS start*/
	OS_start();

	/*infinite loop*/
	for (;;) {

	}
	return 0;
}
