#include <reg51.h>
#include <DS18B20.h>
unsigned char code position[4] = {0xef, 0xdf, 0xbf, 0x7f};	//数码管位选
unsigned char code disp[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};//数码管0~9
sbit P2_7  = P2^7;

void DisplayNum(unsigned int num);

void main()
{
	uint value;
	while(1)
	{
		value = ReadyReadTemp();
		delayms(200);
		P1 = value;
		P2 = value>>8;
		DisplayNum(1234);
	}
}

void DisplayNum(unsigned int num)
{
	unsigned char i;
	for(i=0;i<4;i++)
	{
		P1 = position[i];
		P2 = disp[num%10];
		if(i==2)
		{
			P2_7 = 0;
		}
		num = num/10;
		delayms(1);
		P2 = 0xff;
	}
}
