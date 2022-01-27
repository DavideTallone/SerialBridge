/*
 * Uart.c
 *
 * Created: 27/01/2022 22:48:19
 *  Author: Davide Tallone
 * Brief:	Low level configuration file for the UART peripheral
 *			Uart port configured are. 
 *			SERCOM4 PB08 PB09
 *			SERCOM3	PA22 TX / PA23 RX
 *			SERCOM2	PA12 TX / PA13 RX
 *			
 */ 
#include "Utils.h"
#include "samd21.h"

static unsigned char* ARRAY_PORT_PINCFG0 = (unsigned char* ) &REG_PORT_PINCFG0;
static unsigned char* ARRAY_PORT_PMUX0 = (unsigned char* ) &REG_PORT_PMUX0;

void UART3_Init(void){
	REG_PM_APBCMASK  |= 0x00000020; //enable APB clock
	REG_GCLK_CLKCTRL |= 0x4017;		//enable core clock
	REG_SERCOM3_USART_CTRLA |= 1;	//Reset SERCOM3
	while ( REG_SERCOM3_USART_SYNCBUSY & BIT_TO_MASK32(0) );	//wait for reset do be completed
	REG_SERCOM3_USART_CTRLA |= 0x40106004; // LSB first, no parity, PA22 TX, PA23 RX one stop bit, 8bit
	REG_SERCOM3_USART_CTRLB |= 0x00030000; //Enable Tx and Rx	
	REG_SERCOM3_USART_BAUD = 13;		//1e6/8/9600 = 13.02
	REG_SERCOM3_USART_CTRLA |= 2;	//enable SERCOM3
	while ( REG_SERCOM3_USART_SYNCBUSY & BIT_TO_MASK32(1) );	//wait for reset do be completed
	
	ARRAY_PORT_PINCFG0 [22] = ARRAY_PORT_PINCFG0 [23] |=1;	//enable pin config
	
	ARRAY_PORT_PMUX0[11] = 0x22;		// PA22 = TX PA23 = RX
	
	return;
}

void UART3_Writechar(char data){
	while(! (REG_SERCOM3_USART_INTFLAG & BIT_TO_MASK32(0)) ); //wait for ready to send
	REG_SERCOM3_USART_DATA = data;
	return;
}

char UART3_Readchar (void){
	while(! (REG_SERCOM3_USART_INTFLAG & BIT_TO_MASK32(2)) ); //wait for ready to receive
	return REG_SERCOM3_USART_DATA;
}