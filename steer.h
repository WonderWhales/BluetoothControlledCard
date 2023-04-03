/**
 * @file steer.h
 * @author Jackie Huynh
 * @brief header for basic steering functionality of the car
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
#ifndef STEER_H_
#define STEER_H_

#include "PWM.h"
#include "ButtonLED.h"

#define IN1				0x10
#define IN2				0x20
#define IN3				0x40
#define IN4				0x80

#define STRAIGHT	IN1 | IN3
#define REVERSE		IN2 | IN4
#define LEFT			IN3
#define RIGHT			IN1
#define STOP			0x00

#define DIRECTION	(*((volatile unsigned long*)0x400063C0))

void START_WHEEL(void);

//Changing IN1-4
void DRIVE_LEFT(void);
void DRIVE_RIGHT(void);
void DRIVE_STRAIGHT(void);
void DRIVE_REVERSE(void);

//Duty Cycle Adjustment
void DRIVE_STOP(void);
void SPEED_UP(void);
void SPEED_DOWN(void);

#endif