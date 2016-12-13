#ifndef _DS18B20_H_
#define _DS18B20_H_
#include <reg51.h>
#include <intrins.h>

typedef unsigned char uchar;
typedef unsigned int  uint;

bit Init_DS18B20(void);
uint ReadyReadTemp(void);
void delayms(uchar t);



#endif