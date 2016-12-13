#ifndef _UART_H
#define _UART_H

#include <reg51.h>

extern unsigned char UART_buff;		//存放接受到的数据
extern bit REC_flag, SEND_flag;	//串口数据 接收 发送 完毕的标志位

void uart_int();									//串口初始化函数
unsigned char uart_send(unsigned char send_data);	//串口发送数据函数

#endif
