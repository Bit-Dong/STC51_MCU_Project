#include <reg52.h>
#include "LCD1602.h"
#include "Delay.h"

unsigned int result=0;

void main()
{
		LCD_Init();
	LCD_ShowChar(1,1,'N');
	LCD_ShowChar(1,2,'D');
	LCD_ShowString(1,4,"Hello");
	LCD_ShowNum(1,10,222,3);
	LCD_ShowSignedNum(1,14,-22,2);
	LCD_ShowHexNum(2,1,0xAA,2);
	LCD_ShowBinNum(2,4,0xAB,8);

		while(1);

}
