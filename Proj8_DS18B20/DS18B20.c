#include <DS18B20.h>
sbit DQ  = P3^4;
unsigned char time;	//用于延时

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
	DQ=0; 					//拉低数据总线
	for(time=0;time<200;time++);		//延时480~960us	主机产生复位信号
	DQ=1;				   	//拉高电平释放总线
	for(time=0;time<15;time++);		//等待16~60us	
	flag=DQ;				//读取传感器响应的复位信号 低电平
	for(time=0;time<200;time++);		//延时等待通信结束
	return flag;
}
void WriteOneChar(uchar dat)
{
	uchar i=0;
	for(i=0;i<8;i++)
	{
		DQ=1;
		_nop_();
		DQ=0;				//拉低数据总线
		_nop_();			//延时约1us时间
		DQ=dat&0x01;	   	//输出数据电平
		for(time=0;time<15;time++);	//延时约60us，DS18B20在15~60us对数据采样
		DQ=1; 				//释放数据线
		for(time=0;time<1;time++);	//延时4us，两个写时序间至少需要1us的恢复期
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
		DQ=0;				//拉低数据总线
		_nop_();
		DQ=1; 				//人为拉高释放总线信号，为单片机检测DS18B20的输出电平做准备
		for(time=0;time<2;time++);	//延时约8us 单片机在上面开始拉低起15us内对数据总线信号进行采集
		dat>>=1;
		if(DQ==1) dat|=0x80;
		else dat|=0x00;
		for(time=0;time<15;time++);	//延时约60us，两个读时序间至少需要60us 
	}
	return dat;
}

uint ReadyReadTemp(void)
{
	uchar Temp_H, Temp_L;	//用于存储温度的高8位和低8位
	uint Temp; 
	Init_DS18B20();		   	//复位
	WriteOneChar(0xcc);		//跳过ROM
	WriteOneChar(0x44);		//发送温度变换指令
	delayms(200); 			//等待200ms
	Init_DS18B20();			//复位
	WriteOneChar(0xcc);	 	//跳过ROM读写
	WriteOneChar(0xbe);	  	//发送开始读取温度数据指令
	Temp_L = ReadOneChar();	//先读低8位数据
	Temp_H = ReadOneChar();	//再读高8位数据
	Temp = (Temp_H<<8)+Temp_L;
	if(Temp>0x8000)
	{
		return (~Temp)+1; //温度为负值 18B20输出为补码
	}else{
		return Temp;
	}
}
