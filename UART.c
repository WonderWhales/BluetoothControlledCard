/**
 * @file UART.c
 * @author Jackie Huynh
 * @brief implementation of UART peripheral initialization and basic functionality
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "UART.h"

//----------------------------------UART0----------------------------------------

//Terminal UART Init
//115200 Baudrate
void UART0_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
  UART0_CTL_R = 0;                      // disable UART
  UART0_IBRD_R = 8;                    // IBRD = int(16,000,000 / (16 * 115,200)) = int(8.68)
  UART0_FBRD_R = 44;                     // FBRD = int(0.68 * 64 + 0.5) = 44
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN;// enable Tx, RX and UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}

//Transmit Character to Terminal
void UART0_OutChar(unsigned char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

//Transmit String to Terminal
void UART0_OutString(unsigned char *pt){
  while(*pt){
    UART0_OutChar(*pt);
    pt++;
  }
	UART0_OutChar(0); // add the null terminator
}


//----------------------------------UART1----------------------------------------

//Bluetooth Module UART Init
//57600 Baudrate
void UART1_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
	while((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB) == 0){}; 
		
  UART1_CTL_R = 0;                     // reset UART1
  UART1_IBRD_R = 17;                    // IBRD = int(16,000,000 / (16 * 57600)) = int(17.36111)
  UART1_FBRD_R = 23;                     // FBRD = int(0.36111 * 64 + 0.5) = 23
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)	
	UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= UART_CTL_UARTEN|UART_CTL_RXE|UART_CTL_TXE; // enable UART, Rx, Tx
		
  GPIO_PORTB_AFSEL_R |= 0x03;           // enable alt funct on PB1-0
  GPIO_PORTB_DEN_R |= 0x03;             // enable digital I/O on PB1-0
                                        // configure PB1-0 as UART
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTB_AMSEL_R &= ~0x03;          // disable analog functionality on PB1-0
}

//Bluetooth UART Interrupt Init
//Only used if conditional compilation pass
#ifdef USE_UART1_INTERRUPT
void UART1_INT_Init(void){
	
	//Clock Setup
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
	while((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB) == 0){}; 
		
	//UART1 Default Setup
  UART1_CTL_R &= ~UART_CTL_UARTEN;        // reset UART1
  UART1_IBRD_R = 17;                    		// IBRD = int(16,000,000 / (16 * 57600)) = int(17.36111)
  UART1_FBRD_R = 27;                     	// FBRD = int(0.36111 * 64 + 0.5) = 27
																					// 8 bit word length (no parity bits, one stop bit, no FIFO)
  UART1_LCRH_R |= UART_LCRH_WLEN_8;
		
	//GPIO Setup
	GPIO_PORTB_AFSEL_R |= 0x03;           // enable alt funct on PB1-0
  GPIO_PORTB_DEN_R |= 0x03;             // enable digital I/O on PB1-0
                                        // configure PB1-0 as UART
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTB_AMSEL_R &= ~0x03;          // disable analog functionality on PB1-
	
	//UART1 Interrupt Setup
	UART1_IM_R |= UART_IM_RXIM;						// Enable RX Interrupt Mask
	UART1_ICR_R |= UART_ICR_RXIC;					// Clear RX Interrupt Flag
		
	//UART1 Enable
	UART1_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;
		
	//NVIC UART1 Enable
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFF1FFFFF)|0x00400000; // bits 23-21
  NVIC_EN0_R = NVIC_EN0_UART1;           // enable interrupt 5 in NVIC	
}
#endif

//Receive Character From Bluetooth Module
unsigned char UART1_InChar(void){
  while((UART1_FR_R&UART_FR_RXFE) != 0); // wait until the receiving FIFO is not empty
  return((unsigned char)(UART1_DR_R&0xFF));
}

