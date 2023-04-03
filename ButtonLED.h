/**
 * @file ButtonLED.c
 * @author Jackie Huynh
 * @brief header for RGB LED GPIO initialization
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
#ifndef BUTTONLED_H_
#define BUTTONLED_H_

#include "tm4c123gh6pm.h"

#define LED_PINS				0x0E
#define DARK    				0x00
#define RED   					0x02
#define BLUE    				0x04
#define GREEN  					0x08
#define YELLOW  				0x0A
#define CYAN   					0x0C
#define WHITE   				0x0E
#define PURPLE 					0x06

#define LEDs (*((volatile unsigned long *)0x40025038))

void LED_Init(void);

#endif