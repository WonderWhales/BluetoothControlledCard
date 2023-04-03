/**
 * @file ButtonLED.c
 * @author Jackie Huynh
 * @brief implementation for RGB LED GPIO initialization
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
#include "ButtonLED.h"

void LED_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	while((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)!=SYSCTL_RCGC2_GPIOF){};
		
	GPIO_PORTF_CR_R 		|= LED_PINS;         													// allow changes to PF3-1     
  GPIO_PORTF_AMSEL_R 	&= ~(LED_PINS);        												// disable analog function
  GPIO_PORTF_PCTL_R 	&= ~(0x0000FFF0); 														// GPIO clear bit PCTL  
	GPIO_PORTF_DIR_R 		|= LED_PINS;          												// PF3, PF2, PF1 LED Output  
	GPIO_PORTF_AFSEL_R 	&= ~(LED_PINS);        												// no alternate function
	GPIO_PORTF_PUR_R 		&= ~(LED_PINS);          											// disable pullup resistors on PF3, PF2, PF1 		
  GPIO_PORTF_DEN_R 		|= LED_PINS;  
}