#include <reg52.h>
#include "lcd1602.h"

unsigned char array[] = {"hello word"};
unsigned char i = 0;


void main()
{
	//1.初始化lcd1602
	init_lcd();
	//2.写数据（hello word）到LCD1602显示
	while(array[i] != '\0')
	{	
		write_data(array[i]);
		i++;
	}	
	while(1);
}
