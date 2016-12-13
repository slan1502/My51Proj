#include "iic.h"

/****************************************
* 名称：delay_us
* 输入：无
* 输出：无
* 备注：产生延时信号 
****************************************/
void delay_us()
{
	/*
	while(us--)
	{
		_nop_();
		//_nop_();
	}
	*/
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

/****************************************
* 名称：iic_start
* 输入：无
* 输出：无
* 备注：产生start信号 
****************************************/
void iic_start(void)
{
	SCL = 0;
    SDA = 1;        //需要在SCL之前设定
    delay_us();    //延时至少4.7μs
    SCL = 1;        //硬件进入SDA检测状态
    delay_us();    //延时至少4.7μs
    SDA = 0;        //SDA由1->0，产生开始信号
    delay_us();    //延时至少4μs
    SCL = 0;        //SCL变为无效
}

/****************************************
* 名称：iic_stop
* 输入：无
* 输出：无
* 备注：产生stop信号 
****************************************/
void iic_stop(void)
{
    SDA = 0;        //在SCL之前拉低
    delay_us();    //至少延时4us
    SCL = 1;        //硬件进入SDA检测状态
    delay_us();    //至少延时4us
    SDA = 1;        //SDA由0->1产生结束信号
    delay_us();    //延时至少4.7us
	SCL = 0;
}

/****************************************
* 名称：iic_write_byte
* 输入：dat需要写入的数据
* 输出：无
* 备注：iic写一个字节
****************************************/
void iic_write_byte(uchar dat)
{
    uchar loop = 8;     //一个字节循环8次
    while(loop--){
        SDA = dat&0x80; //从高位开始逐位写入
        SCL = 1;
        delay_us();    //至少延时4us
        SCL = 0;
        dat <<= 1;      //低位向高位移动
        delay_us();
    }
}

/****************************************
* 名称：iic_read_byte
* 输入：无
* 输出：读取到的数据
* 备注：iic读取一个字节
****************************************/
uchar iic_read_byte(void)
{
    uchar loop = 8;     //一个字节循环8次
    uchar ret = 0;
    while(loop--){
        SDA = 1;        //8051内部电阻上拉
        SCL = 1;
        delay_us();    //至少延时4us
        ret <<= 1;
        ret |= SDA;     //读取1位
        SCL = 0  ;
        delay_us();
    }
    return ret;
}

/****************************************
* 名称：iic_send_ack
* 输入：应答信号  0-ACK 1-NAK
* 输出：无
* 备注：由主机向从机发送应答码 0-ACK 1-NAK
****************************************/
void iic_send_ack(bit ack)
{
    SDA = ack;      //产生应答电平
    SCL = 1;        //发送应答信号
    delay_us();    //至少延时4us
    SCL = 0;        //整个期间保持应答信号
}

/****************************************
* 名称：iic_get_ack
* 输入：无
* 输出：无
* 备注：取得由从机到主机的应答信号 0-ACK 1-NAK
****************************************/
bit iic_get_ack(void)
{
    bit ret;        
    SDA = 1;        //电阻上拉 进入读(8051)
    SCL = 1;        //进入应答检测
    delay_us();    //至少延时4us
    ret = SDA;      //保存应答信号
    SCL = 0;
    return ret;
}