/**
 * @file PWM.c
 * @author Jackie Huynh
 * @brief implementation for PWM peripheral initialization and basic functionality
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "PWM.h"

//PB7 M0PWM1 PB6 M0PWM0
void WHEEL_PWM_Init(void){
	
	//GPIO Init
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
	while((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB)!=SYSCTL_RCGC2_GPIOB);
	
	GPIO_PORTB_AFSEL_R |= PWM_PINS;						// enable alt funct: PB76 for PWM
  GPIO_PORTB_PCTL_R &= ~0xFF000000; 				// PWM to be used
  GPIO_PORTB_PCTL_R |= 0x44000000; 					// PWM to be used
  GPIO_PORTB_DEN_R |= PWM_PINS;							// enable digital I/O
	
	//PWM Module Init
	SYSCTL_RCGCPWM_R = SYSCTL_RCGCPWM_R0;			//Enable PWM Module 0
	while((SYSCTL_RCGCPWM_R&SYSCTL_RCGCPWM_R0)!=SYSCTL_RCGCPWM_R0);
	
	SYSCTL_RCC_R &= ~0x001E0000; 							// Clear any previous PWM divider values
	PWM0_0_CTL_R = 0;													// Default Mode of reloading countdown
	PWM0_0_GENA_R |= 0xC8;										// low on LOAD, high on CMPA down
	PWM0_0_GENB_R |= 0xC08;										// low on LOAD, high on CMPB down
	PWM0_0_LOAD_R = PERIOD - 1;								// 16MHz/16000 = 1kHz Frequency
  PWM0_0_CMPA_R = 0;												// 0% Duty Cycle for PB6
	PWM0_0_CMPB_R = 0;												// 0% Duty Cycle for PB7
	
	PWM0_0_CTL_R |= PWM_0_CTL_ENABLE;					//Enable Counter Mode
	PWM0_ENABLE_R &= ~(PWM_ENABLE_PWM0EN | PWM_ENABLE_PWM1EN);	//Disable PWM Module
}

//Initializes PC7-4 to control IN1-4
void DIR_GPIO_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;
	while((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOC)!= SYSCTL_RCGC2_GPIOC);
	
	GPIO_PORTC_CR_R 		|= DIR_PINS;         	// allow changes to PC7-4    
  GPIO_PORTC_AMSEL_R 	&= ~(DIR_PINS);       // disable analog function
  GPIO_PORTC_PCTL_R 	&= ~(0xFFFF0000); 		// GPIO clear bit PCTL  
	GPIO_PORTC_DIR_R 		|= DIR_PINS;         	// PC7-4 Output  
	GPIO_PORTC_AFSEL_R 	&= ~(DIR_PINS);       // no alternate function
	GPIO_PORTC_PUR_R 		&= ~(DIR_PINS);       // disable pullup resistors		
  GPIO_PORTC_DEN_R 		|= DIR_PINS;  				// enable digital pin
}

void DRIVE_WHEEL(uint16_t left_duty, uint16_t right_duty){
	PWM0_0_CMPA_R = right_duty;
	PWM0_0_CMPB_R = left_duty;
}

