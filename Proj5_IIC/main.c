#include <reg51.h>
#include "uart.h"
#include "smg.h"
#include "iic.h"

void delayms(uint t)
{
	uchar k;
	while(t--)
	{
		for(k=0;k<120;k++);
	}
}

void sendbyte(uchar num, uint addr)
{
	iic_start();
	iic_write_byte(0xa0);
	iic_get_ack();
	iic_write_byte(addr>>8);
	iic_get_ack();
	iic_write_byte(addr);
	iic_get_ack();
	iic_write_byte(num);
	iic_get_ack();
	iic_stop();
	delayms(10);
}

uchar readbyte(uchar addr)
{
	uchar dat;
	iic_start();
	iic_write_byte(0xa0);
	iic_get_ack();
	iic_write_byte(addr>>8);
	iic_get_ack();
	iic_write_byte(addr);
	iic_get_ack();
	iic_start();
	iic_write_byte(0xa1);
	iic_get_ack();
	dat = iic_read_byte();
	iic_get_ack();
	iic_stop();
	//delayms(30);
	return dat;
}	
void main()
{
	uint d, t;
	uart_int();
	for(d=0;d<0x0f;d++)
	{
		t = readbyte(d);
		while(!uart_send(t));
		sendbyte(t+1,d);
	}
	while(1)
	{
	}
}