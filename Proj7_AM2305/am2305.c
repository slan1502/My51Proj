#include "am2305.h"
unsigned char get_byte();

//大约延时10us
void delay10us(unsigned char t)
{
	while(t--)_nop_();
}

/****************************************
* 名称：get_am2305
* 输入：value 保存从am2305读取到的数据
* 输出：成功返回1 否则0
* 备注： 
****************************************/
unsigned char get_am2305(unsigned char value[5])
{
	unsigned char us, i;	
	AM2305_SDA = 0;		//把总线拉低
	delay10us(100);		//延时至少800us
	AM2305_SDA = 1;		//释放总线
	delay10us(2);		//等待30us左右检测响应信号
	if(!AM2305_SDA)
	{
		EA = 0;				//关闭总中断，确保连续读取am2305
		while(!AM2305_SDA);	//等待低电平
		while(AM2305_SDA);	//等待约80us的高电平响应信号
		for(i=0;i<5;i++)
		{
			value[i] = get_byte();
		}
		EA = 1;				//数据接收完毕后重新打开总中断
		return 1;			//数据采集成功返回1
	}
	return 0;
}

/****************************************
* 名称：get_bit
* 输入：无
* 输出：无
* 备注：从am2305读取一位数据 
****************************************/
unsigned char get_byte()
{
	unsigned char i, buffer;
	buffer = 0;
	for(i=0;i<8;i++)
	{
		while(!AM2305_SDA);	//每个数据位前总线拉低50us
		delay10us(2);		//消除26-28us的位数据
		buffer <<= 1;			
		buffer |= AM2305_SDA;
		while(AM2305_SDA);	//等待本次位数据的高电平释放
	}
	return buffer;
}

		

