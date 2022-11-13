#include <reg52.h>
#include "Delay.h"


#define key P1     
typedef unsigned char u8;
typedef unsigned int u16;

u8 keyvalue;  

unsigned char MatrixKey()
{

	key=0x0f;
	if(key!=0x0f)
	{
		Delay(100);
		if(key!=0x0f)
		{
			key=0x0f;
			switch(key)
			{
				case 0x07 : keyvalue=1;break;
				case 0x0b : keyvalue=2;break;
				case 0x0d : keyvalue=3;break;
				case 0x0e : keyvalue=4;break;
			}
			key=0xf0;
			switch(key)
			{
				case 0x70 : keyvalue=keyvalue;break;
				case 0xb0 : keyvalue=keyvalue+4;break;
				case 0xd0 : keyvalue=keyvalue+8;break;
				case 0xe0 : keyvalue=keyvalue+12;break;
			}
			return keyvalue;
		}
	}
}
