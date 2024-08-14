/*
 * mini_project4.c
 *
 *  Created on: Jul 2, 2023
 *      Author: ahmed
 */
#include"gpio.h"
#include"icu.h"
#include"lcd.h"
#include"avr/io.h"


int main(void){
	uint8 distance;
Ultrasonic_init(); /* initialize the ultrasonic sensor */

LCD_init();  /* initialize the lcd screen */
LCD_moveCursor(0,0);   //initialize the cursor at zero row and col.
SREG|=(1<<7);   // enable the global enterrupt bit
	while(1){
LCD_moveCursor(0,0);
LCD_displayString("distance=");
LCD_moveCursor(0,9);
distance=Ultrasonic_readDistance();  // get the distance from the sensor
if(distance >= 100)
		{
			LCD_intgerToString(distance);
		}
		else
		{
			LCD_intgerToString(distance);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

	}
	return 0;
}




