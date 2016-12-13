#ifndef _SPI_H
#define _SPI_H
#include <reg51.h>

sbit   CS	=   P3^1;  
sbit   CLK	=   P3^2;  
sbit   MOSI	=   P3^4;  
sbit   MISO	=   P3^3;  

void spi_reset();  
void spi_write(unsigned char spi_bValue);  
unsigned char spi_read();  

#endif