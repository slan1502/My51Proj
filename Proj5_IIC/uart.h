#ifndef _UART_H
#define _UART_H

#include <reg51.h>

extern unsigned char UART_buff;		//��Ž��ܵ�������
extern bit REC_flag, SEND_flag;	//�������� ���� ���� ��ϵı�־λ

void uart_int();									//���ڳ�ʼ������
unsigned char uart_send(unsigned char send_data);	//���ڷ������ݺ���

#endif
