#include <reg51.h>
#include "DS12887.h"
#include "uart.h"
#include "smg.h"
void delay(unsigned int t)
{
	unsigned char k;
	while(t--)
	{
		for(k=0;k<200;k++);
	}
}

void main()
{
	uart_int();
	//while(!uart_send(0xaa));
	//while(!uart_send(0xbb));
	DS12887_A = 0x20;
	DS12887_B = 0x06;
	//while(!SEND_flag);	
	while(1)
	{
		//delay(200);
		//read_DS12887();
		display_4SMG(DS12887_A);
	}
}
/*
void main()
{
	P1 = 0x01;
	while(1);
}
*/

