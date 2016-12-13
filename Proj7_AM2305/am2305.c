#include "am2305.h"
unsigned char get_byte();

//��Լ��ʱ10us
void delay10us(unsigned char t)
{
	while(t--)_nop_();
}

/****************************************
* ���ƣ�get_am2305
* ���룺value �����am2305��ȡ��������
* ������ɹ�����1 ����0
* ��ע�� 
****************************************/
unsigned char get_am2305(unsigned char value[5])
{
	unsigned char us, i;	
	AM2305_SDA = 0;		//����������
	delay10us(100);		//��ʱ����800us
	AM2305_SDA = 1;		//�ͷ�����
	delay10us(2);		//�ȴ�30us���Ҽ����Ӧ�ź�
	if(!AM2305_SDA)
	{
		EA = 0;				//�ر����жϣ�ȷ��������ȡam2305
		while(!AM2305_SDA);	//�ȴ��͵�ƽ
		while(AM2305_SDA);	//�ȴ�Լ80us�ĸߵ�ƽ��Ӧ�ź�
		for(i=0;i<5;i++)
		{
			value[i] = get_byte();
		}
		EA = 1;				//���ݽ�����Ϻ����´����ж�
		return 1;			//���ݲɼ��ɹ�����1
	}
	return 0;
}

/****************************************
* ���ƣ�get_bit
* ���룺��
* �������
* ��ע����am2305��ȡһλ���� 
****************************************/
unsigned char get_byte()
{
	unsigned char i, buffer;
	buffer = 0;
	for(i=0;i<8;i++)
	{
		while(!AM2305_SDA);	//ÿ������λǰ��������50us
		delay10us(2);		//����26-28us��λ����
		buffer <<= 1;			
		buffer |= AM2305_SDA;
		while(AM2305_SDA);	//�ȴ�����λ���ݵĸߵ�ƽ�ͷ�
	}
	return buffer;
}

		

