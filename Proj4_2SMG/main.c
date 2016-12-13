#include <reg51.h>
code unsigned char disp[] = {0xfc, 0x0c, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6};
sbit SLCK = P2^4;

void display_2SMG(unsigned char num)
{
	if(num>99)
	{
		return;
	}
	SBUF = disp[num/10];
	while(!TI);
	TI = 0;
	SLCK = 0;
	SLCK = 1;
	SBUF = disp[num%10];
	while(!TI);
	TI = 0;
	SLCK = 0;
	SLCK = 1;
}

void main()
{
	SCON = 0X00;
	display_2SMG(35);
	while(1);
}