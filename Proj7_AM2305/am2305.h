#ifndef _AM2305_H
#define _AM2305_H
#include <reg51.h>
#include <intrins.h>

sbit AM2305_SDA = P0^7;

unsigned char get_am2305(unsigned char value[5]);

#endif