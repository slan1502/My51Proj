#ifndef _DS12887_H
#define _DS12887_H
#include <reg51.h>
#include <absacc.h>

#define DS12887_SEC				XBYTE[0X0100]
#define DS12887_SEC_ALARM		XBYTE[0X0101]
#define DS12887_MIN				XBYTE[0X0102]
#define DS12887_MIN_ALARM		XBYTE[0X0103]
#define DS12887_HOU				XBYTE[0X0104]
#define DS12887_HOU_ALARM		XBYTE[0X0105]
#define DS12887_WEEK			XBYTE[0X0106]
#define DS12887_DAY				XBYTE[0X0107]
#define DS12887_MONTH			XBYTE[0X0108]
#define DS12887_YEAR			XBYTE[0X0109]
#define DS12887_A				XBYTE[0X010A]
#define DS12887_B				XBYTE[0X010B]
#define DS12887_C				XBYTE[0X010C]
#define DS12887_D				XBYTE[0X010D]

extern TimeType;			//存放时间数据的结构体

void read_DS12887();		//读取12887的时间和日期


#endif 