#include <reg51.h>

unsigned char UART_buff;		//存放接受到的数据
bit REC_flag=0, SEND_flag=1;	//串口数据 接收 发送 完毕的标志位

void uart_int();									//串口初始化函数
unsigned char uart_send(unsigned char send_data);	//串口发送数据函数

void main()
{
	unsigned char t=0;
	P1 = 0xaa;
	uart_int();
	EA  = 1;
	uart_send(0xab);
	while(1)
	{
		if(SEND_flag==1)
		{
			uart_send(t++);
		}
	}
}

/****************************************
* 名称：uart_int
* 输入：无
* 输出：无
* 备注：默认波特率为9600 
****************************************/
void uart_int()
{
	SCON = 0x50;   //串口方式1, 8-n-1, 允许接收.  
    TMOD = 0x20;   //T1方式2  
    TH1 = 0xFD;    //9600bps@11.0592MHz[/url]  
    TL1 = 0xFD;  
    TR1 = 1;                          
    ES  = 1;       //开中断.  
}

/****************************************
* 名称：uart_send
* 输入：send_data 发送的数据
* 输出：err 发送是否成功
* 备注：串口发送一个字节
****************************************/
unsigned char uart_send(unsigned char send_data)
{
	if(SEND_flag==1)	//检测上一次发送是否完成
	{
		SBUF = send_data;
		SEND_flag = 0;
		return 1;
	}
	return 0;		
}
/*------------------------------------------------------*/
/****************************************
* 名称：uart_interrupt
* 输入：无
* 输出：无
* 备注：串口中断处理函数
****************************************/
void uart_interrupt() interrupt 4
{
	if(RI==1)	//接收中断
	{
		RI = 0;
		UART_buff = SBUF;	//获取接收数据
		REC_flag = 1;		//接收到数据标志位
	}else{		//发送中断
		TI = 0;
		SEND_flag = 1;
	}
}
/*------------------------------------------------------*/
