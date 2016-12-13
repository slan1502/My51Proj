#include "spi.h"

#define set_spi_cs()	CS 		=1  
#define clr_spi_cs()	CS   	=0  
#define set_spi_clk()	CLK   	=1  
#define clr_spi_clk()   CLK   	=0  
#define set_spi_di() 	MOSI   	=1  
#define clr_spi_di() 	MOSI   	=0  
#define read_spi_do()  	MISO      

/****************************************
* ���ƣ�spi_reset
* ���룺��
* �������
* ��ע����λоƬ������CS�ܽ�
****************************************/
void spi_reset()  
{  
  set_spi_cs();    
}  

/****************************************
* ���ƣ�spi_write
* ���룺spi_bValue ͨ��spiд������
* �������
* ��ע��spiд����
****************************************/
void spi_write(unsigned char spi_bValue)  
{  
	unsigned   char   no;  
	clr_spi_cs();			//Ƭѡʹ���豸  
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
* ���ƣ�spi_read
* ���룺��
* �������ȡ��������
* ��ע��spi������
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