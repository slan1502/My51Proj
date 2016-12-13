#include "smg.h"

code unsigned char Num_Data[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
code unsigned char Num_addr[] = {0xef, 0xdf, 0xbf, 0x7f};

void delay_smg(unsigned char t)
{
	unsigned char k;
	while(t--)
	{
		for(k=0;k<50;k++);
	}
}

/****************************************
* 名称：display_4SMG
* 输入：4位数码管显示的值
* 输出：如果输入参数超过9999 则返回0
* 备注：
****************************************/
unsigned char display_4SMG(unsigned int num)
{
	unsigned char i, P1_temp;
	if(num>9999)	//4位数码管不能显示超过9999
	{
		return 0;
	}
	for(i=0;i<4;i++)
	{
		P1_temp = P1;
		P1 = P1&Num_addr[i];
		P2 = Num_Data[num%10];
		num = num/10;
		delay_smg(10);
		P1 = P1_temp;
		P2 = 0xff;
	}
	return 1;
}
