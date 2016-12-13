#include <reg51.h>
#include "uart.h"
#include "am2305.h"

void delayms(unsigned int t)
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<120;i++);
	}
}

void main()
{
	unsigned char get_value[5]={0,1,2,3,4}, check;
	uart_int();
	while(!uart_send(get_value[0]));
	while(!uart_send(get_value[1]));
	while(!uart_send(get_value[2]));
	while(!uart_send(get_value[3]));
	while(!uart_send(get_value[4]));
	delayms(2000);		//开机等待2s 确保越过am2305的不稳定状态
	while(1)
	{
		P1 = ~P1;
		delayms(4000);		//3s采集一次数据
		/*
		get_am2305(get_value);
		*/
		if(get_am2305(get_value))
		{
			check = 0;
			check = get_value[0]+get_value[1]+get_value[2]+get_value[3];
			if(check==get_value[4])
			{
				while(!uart_send(get_value[0]));
				while(!uart_send(get_value[1]));
				while(!uart_send(get_value[2]));
				while(!uart_send(get_value[3]));
				while(!uart_send(get_value[4]));
			}
		}else{
			while(!uart_send(0xff));
		}
	}
}