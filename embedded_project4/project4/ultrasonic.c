/*
 * ultrasonic.c
 *
 *  Created on: Jul 3, 2023
 *      Author: ahmed
 */

#include"ultrasonic.h"
#include"avr/io.h"
#include"icu.h"
#include"util/delay.h"
/*--------------------------------------------------GLOBAL VARIABLES----------------------------------------------------*/

uint16 time_width,edge_count=0;

/*-----------------------------------------------------------------------------------------------------------------------*/

/* Function discription :- this is the call back function which is called by the icu after catching the required edge
 * first call: - raising edge detection we will clear the timer to start counting the width
 * second call: - after catching the falling edge we get the timer value which is the pulse width time
 *
 */
void Ultrasonic_edgeProcessing(void){
edge_count++;   /* increment the count each time we enter the func to control each entry */
if(edge_count==1){
ICU_clearTimerValue();  //clear the timer value to start counting the signal width time
ICU_setEdgeDetectionType(FALLING);  //change the detection direction to falling so we can get the width time
}
else if(edge_count==2){
time_width =ICU_getInputCaptureValue();  /* the second entry we catched the falling edge so this is the time we want */
ICU_setEdgeDetectionType(RAISING);   // re initialize the icu to start working again.
edge_count=0;
}
}
/*----------------------------------------------------------------------------------------------------------------------*/

/* Function discription :- this function to send the initiation structure to the icu to initialize it and to set the
 * direction of the pins used by the sensor .
 * and to call the call back function of the icu.
 *
 */
void Ultrasonic_init(void){
	ICU_ConfigType ICU_init_s,*ICU_init_ptr;
	ICU_init_ptr= &ICU_init_s;
	ICU_init_ptr->clock =F_CPU_8;
	ICU_init_ptr->edge =RAISING;
ICU_init(ICU_init_ptr);
DDRB|=(1<<PB5);   //setting trigger pin as output
DDRD&=~(1<<PD6);  // setting echo pin as input
ICU_setCallBack(Ultrasonic_edgeProcessing);  // calling the call back function.
}
/*-----------------------------------------------------------------------------------------------------------------------*/

/* Function discription:- this function is to set the trigger signal to the sensor.
 *
 */
void Ultrasonic_trigger(void){
	PORTB|=(1<<PB5);
	_delay_us(10);
	PORTB&=~(1<<PB5);
}
/*-----------------------------------------------------------------------------------------------------------------------*/

/* Function discription: - this function is used to start the sensing by triggering the sensor and to get the distance
 * output of the sensor.
 *
 */
uint16 Ultrasonic_readDistance(void){
	uint16 distance;
	Ultrasonic_trigger();

	distance =0.017*time_width; // the formula used to calculate the distance
	if(distance<57){
	return distance+1;
	}
	else if(distance>=57&&distance<129){
		return distance+2;
	}
	else{
		return distance+3;
	}
}














