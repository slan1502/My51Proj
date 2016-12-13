#include <DS18B20.h>
sbit DQ  = P3^4;
unsigned char time;	//������ʱ

void delayms(uchar t)
{
	uchar i;
	while(t--)
	{
		for(i=0;i<123;i++);
	}
}

bit Init_DS18B20(void)
{
	bit flag;
	DQ=1;
	_nop_(); 
	DQ=0; 					//������������
	for(time=0;time<200;time++);		//��ʱ480~960us	����������λ�ź�
	DQ=1;				   	//���ߵ�ƽ�ͷ�����
	for(time=0;time<15;time++);		//�ȴ�16~60us	
	flag=DQ;				//��ȡ��������Ӧ�ĸ�λ�ź� �͵�ƽ
	for(time=0;time<200;time++);		//��ʱ�ȴ�ͨ�Ž���
	return flag;
}
void WriteOneChar(uchar dat)
{
	uchar i=0;
	for(i=0;i<8;i++)
	{
		DQ=1;
		_nop_();
		DQ=0;				//������������
		_nop_();			//��ʱԼ1usʱ��
		DQ=dat&0x01;	   	//������ݵ�ƽ
		for(time=0;time<15;time++);	//��ʱԼ60us��DS18B20��15~60us�����ݲ���
		DQ=1; 				//�ͷ�������
		for(time=0;time<1;time++);	//��ʱ4us������дʱ���������Ҫ1us�Ļָ���
		dat>>=1;
	}
	for(time=0;time<4;time++);
}

uchar ReadOneChar(void)
{
	uchar i=0;
	uchar dat;
	for(i=0;i<8;i++)
	{
		DQ=1;
		_nop_();
		DQ=0;				//������������
		_nop_();
		DQ=1; 				//��Ϊ�����ͷ������źţ�Ϊ��Ƭ�����DS18B20�������ƽ��׼��
		for(time=0;time<2;time++);	//��ʱԼ8us ��Ƭ�������濪ʼ������15us�ڶ����������źŽ��вɼ�
		dat>>=1;
		if(DQ==1) dat|=0x80;
		else dat|=0x00;
		for(time=0;time<15;time++);	//��ʱԼ60us��������ʱ���������Ҫ60us 
	}
	return dat;
}

uint ReadyReadTemp(void)
{
	uchar Temp_H, Temp_L;	//���ڴ洢�¶ȵĸ�8λ�͵�8λ
	uint Temp; 
	Init_DS18B20();		   	//��λ
	WriteOneChar(0xcc);		//����ROM
	WriteOneChar(0x44);		//�����¶ȱ任ָ��
	delayms(200); 			//�ȴ�200ms
	Init_DS18B20();			//��λ
	WriteOneChar(0xcc);	 	//����ROM��д
	WriteOneChar(0xbe);	  	//���Ϳ�ʼ��ȡ�¶�����ָ��
	Temp_L = ReadOneChar();	//�ȶ���8λ����
	Temp_H = ReadOneChar();	//�ٶ���8λ����
	Temp = (Temp_H<<8)+Temp_L;
	if(Temp>0x8000)
	{
		return (~Temp)+1; //�¶�Ϊ��ֵ 18B20���Ϊ����
	}else{
		return Temp;
	}
}
