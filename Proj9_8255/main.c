#include <reg51.h>
#include <ABSACC.h>

#define uchar unsigned char
#define uint unsigned int
#define COM8255	XBYTE[0XFFFF]
#define PA8255	XBYTE[0XFFFC]
#define PB8255	XBYTE[0XFFFD]
#define PC8255	XBYTE[0XFFFE]

code unsigned char disp[] = {0xfc, 0x0c, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6};
code unsigned char keyNum[] = {0xee, 0xde, 0xbe, 0x7e,	\
							   0xed, 0xdd, 0xbd, 0x7d, 	\
							   0xeb, 0xdb, 0xbb, 0x7b,	\
							   0xe7, 0xd7, 0xb7, 0x77};

sbit SLCK = P2^4;

sbit P1_2 = P1^2;
sbit P1_1 = P1^1;
sbit P1_0 = P1^0;

uchar keyScan();
void display_2SMG(unsigned char num);
void delay(uchar t)
{
	uchar k;
	while(t--)
	{
		for(k=0;k<100;k++);
	}
}

void main()
{
	uchar get_key, i;
	SCON = 0X00;
	display_2SMG(99);
	while(1)
	{
		get_key = keyScan();	//�õ�������
		//��ѯ�������Ӧ�İ����� �����2λ�������
		for(i=0; i<16; i++)
		{
			if(keyNum[i]==get_key)
			{
				display_2SMG(i);
				break;
			}
		}	
	}
}

/*�������ɨ�躯��*/
uchar keyScan()
{
	uchar keyGet=0xff, i;
	//ͨ��138������ѡ��8255Ƭѡ
	P1_2 = 0;
	P1_1 = 1;
	P1_0 = 0;
	COM8255 = 0X82;		//C����� B�����뷽ʽ

	for(i=0;i<4;i++)		//�ӵ�һ�п�ʼɨ�赽������
	{
		PC8255 = ~(1<<i);	//C�ڶ�Ӧ�������0 ����1
		if(PB8255 != 0xff)	//����Ƿ��а�������
		{					//��ʱ ����������������
			delay(3);
			if(PB8255 != 0xff)
			{
				keyGet = PC8255&PB8255;	//B�ڸ�4λ��C�ڵ���λ��ɰ�����
				break;
			}
		}
	}
	return keyGet;	//���ذ����� û�а�������0XFF
}

/*��λ�������ʾ����*/
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
	
