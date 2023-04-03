/**
 * @file main.c
 * @author Jackie Huynh
 * @brief main execution of the program
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "UART.h"
#include "PWM.h"
#include "steer.h"
#include "ButtonLED.h"

int main(void){
	
	LED_Init();
	DIR_GPIO_Init();
	WHEEL_PWM_Init();
	UART0_Init();
	
	#ifdef USE_UART1_INTERRUPT
		UART1_INT_Init();
	#else
		UART1_Init();
	#endif
	
	START_WHEEL();
	
	while(1){
		
		#ifdef USE_UART1_Interrupt
		switch(getData()){
		#else
		switch(UART1_InChar()){
		#endif
			
			case 'F':
				DRIVE_STRAIGHT();
				break;
			case 'B':
				DRIVE_REVERSE();
				break;
			case 'L':
				DRIVE_LEFT();
				break;
			case 'R':
				DRIVE_RIGHT();
				break;
			case 'S':
				DRIVE_STOP();
				break;
			case 'U':
				SPEED_UP();
				break;
			case 'D':
				SPEED_DOWN();
				break;
			default:
				break;
		}
	}
	
	return 0;
}
 