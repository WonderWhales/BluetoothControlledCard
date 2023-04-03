/**
 * @file steer.c
 * @author Jackie Huynh
 * @brief implementation for basic steering functionality of the car
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
#include "steer.h"

const uint16_t SPEED_ARRAY[] = {0, PERIOD*0.1-1, PERIOD*0.2-1, PERIOD*0.3-1, PERIOD*0.4-1, PERIOD*0.5-1, 
																PERIOD*0.6-1, PERIOD*0.7-1, PERIOD*0.8-1, PERIOD*0.9-1, PERIOD-2};
uint8_t stepsCNT = 5;

//Start Car																
void START_WHEEL(void){
	PWM0_0_CMPA_R = SPEED_ARRAY[5];
	PWM0_0_CMPB_R = SPEED_ARRAY[5];
	PWM0_ENABLE_R |= PWM_ENABLE_PWM0EN | PWM_ENABLE_PWM1EN;
}
																
//--------------------------------------Direction Mod-----------------------------------------------														
void DRIVE_LEFT(void){
	DIRECTION = LEFT;
	LEDs = YELLOW;
}

void DRIVE_RIGHT(void){
	DIRECTION = RIGHT;
	LEDs = PURPLE;
}

void DRIVE_STRAIGHT(void){
	DIRECTION = STRAIGHT;
	LEDs = GREEN;
}

void DRIVE_REVERSE(void){
	DIRECTION = REVERSE;
	LEDs = BLUE;
}

//--------------------------------------Duty Cycle Mod-----------------------------------------------
void DRIVE_STOP(void){
	DIRECTION = STOP;
	LEDs = DARK;
}

void SPEED_UP(void){
	stepsCNT++;
	if(stepsCNT > 10)
		stepsCNT = 10;
	DRIVE_WHEEL(SPEED_ARRAY[stepsCNT], SPEED_ARRAY[stepsCNT]);
}

void SPEED_DOWN(void){
	stepsCNT--;
	if(stepsCNT == 0)
		stepsCNT = 0;
	DRIVE_WHEEL(SPEED_ARRAY[stepsCNT], SPEED_ARRAY[stepsCNT]);
}
