#ifndef _IIC_H
#define _IIC_H
#include <reg51.h>
#include <intrins.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

sbit SDA = P3^2;
sbit SCL = P3^4;

void iic_start(void);
void iic_stop(void);
bit iic_get_ack(void);
void iic_write_byte(uchar dat);
uchar iic_read_byte(void);
void iic_send_ack(bit ack);

#endif