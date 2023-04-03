/**
 * @file UART.h
 * @author Jackie Huynh
 * @brief header for UART peripheral initialization
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef UART_H_
#define UART_H_

//Conditional Compilation Macros
//#define USE_UART1_INTERRUPT

#include "tm4c123gh6pm.h"

#define NVIC_EN0_UART1		0x40

//UART0 Functions
void UART0_Init(void);
void UART0_OutChar(unsigned char);
void UART0_OutString(unsigned char*);

//UART1 Functions
void UART1_Init(void);
void UART1_INT_Init(void);
unsigned char UART1_InChar(void);

#endif
