#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MDIO_interface.h"
#include "H7Segments_private.h"
#include "H7Segments_interface.h"

void H7Seg_clear(void) {
	MDIO_SetPinOutput(PORTC, 0, HIGH);
	MDIO_SetPinOutput(PORTC, 1, HIGH);
	MDIO_SetPinOutput(PORTC, 2, HIGH);
	MDIO_SetPinOutput(PORTC, 3, HIGH);
	MDIO_SetPinOutput(PORTC, 4, HIGH);
	MDIO_SetPinOutput(PORTC, 5, HIGH);
	MDIO_SetPinOutput(PORTC, 6, HIGH);
	return;
}

void H7Seg_initialize(void) {
	MDIO_SetPinDirection(PORTC, 0, OUTPUT);
	MDIO_SetPinDirection(PORTC, 1, OUTPUT);
	MDIO_SetPinDirection(PORTC, 2, OUTPUT);
	MDIO_SetPinDirection(PORTC, 3, OUTPUT);
	MDIO_SetPinDirection(PORTC, 4, OUTPUT);
	MDIO_SetPinDirection(PORTC, 5, OUTPUT);
	MDIO_SetPinDirection(PORTC, 6, OUTPUT);

	H7Seg_clear();
	return;
}

void H7Seg_display(uint8 num) {
	H7Seg_clear();
	for (int j=0; numbers[num][j] != -1; j++)
//		PORTC &= ~(0b00000001 << numbers[number][j]);	// Set PORTC bits at numbers to 0
		MDIO_SetPinOutput(PORTC, numbers[num][j], LOW);
	return;
}
