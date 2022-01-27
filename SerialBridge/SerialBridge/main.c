/*
 * SerialBridge.c
 *
 * Created: 27/01/2022 22:46:24
 * Author : Davide
 */ 


#include "sam.h"
#include "Uart.h"

void delayms(int n);

int main(void)
{
	UART3_Init();
    /* Replace with your application code */
    while (1) 
    {

		UART3_Writechar(UART3_Readchar());
		delayms(10);
    }
}


void delayms(int n){
	int i;
	for(; n>0 ; n--){
		for(i=0; i<199 ; i++){
			__asm("nop");
		}
	}
	return;
}