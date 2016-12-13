#include "DS12887.h"
#include "uart.h"

struct
{
	unsigned char sec;
	unsigned char min;
	unsigned char hou;
	unsigned char week;
	unsigned char day;
	unsigned char mon;
	unsigned char year;
}TimeType;

void read_DS12887()
{
	//TimeType.sec = DS12887_SEC;
	uart_send(DS12887_A);
}