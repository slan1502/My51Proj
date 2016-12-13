#include "spi.h"

#define set_spi_cs()	CS 		=1  
#define clr_spi_cs()	CS   	=0  
#define set_spi_clk()	CLK   	=1  
#define clr_spi_clk()   CLK   	=0  
#define set_spi_di() 	MOSI   	=1  
#define clr_spi_di() 	MOSI   	=0  
#define read_spi_do()  	MISO      

/****************************************
* 名称：spi_reset
* 输入：无
* 输出：无
* 备注：复位芯片，拉高CS管脚
****************************************/
void spi_reset()  
{  
  set_spi_cs();    
}  

/****************************************
* 名称：spi_write
* 输入：spi_bValue 通过spi写的数据
* 输出：无
* 备注：spi写数据
****************************************/
void spi_write(unsigned char spi_bValue)  
{  
	unsigned   char   no;  
	clr_spi_cs();			//片选使能设备  
	for (no=0;no<8;no++)  
	{  
		clr_spi_clk();      
		if((spi_bValue&0x80)==0x80)  
		    set_spi_di();  
		else  
		    clr_spi_di();  
		set_spi_clk();    
		spi_bValue = (spi_bValue<<1);  
	}  
}  

/****************************************
* 名称：spi_read
* 输入：无
* 输出：读取到的数据
* 备注：spi读数据
****************************************/
unsigned char spi_read()  
{  
	unsigned char no,spi_bValue;  
	clr_spi_cs();  
	for (no=0;no<8;no++)  
	{                                                                  
		clr_spi_clk();
		spi_bValue = (spi_bValue<<1);  
		set_spi_clk();  
		if(read_spi_do()==1)  
			spi_bValue |= 0x01;  
		else  
		    spi_bValue &= (~0x01);  
	}  
	return spi_bValue;  
}   