/**
 * @file PWM.h
 * @author Jackie Huynh
 * @brief header for PWM peripheral initialization
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
 
#ifndef PWM_H_
#define PWM_H_

#include "tm4c123gh6pm.h"
#include <stdint.h>

#define DIR_PINS	0xF0
#define PWM_PINS	0xC0
#define PERIOD		16000

void WHEEL_PWM_Init(void);
void DIR_GPIO_Init(void);
void DRIVE_WHEEL(uint16_t, uint16_t);

#endif