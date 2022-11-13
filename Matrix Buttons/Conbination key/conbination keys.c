#include <reg52.h>
#include "Delay.h"		//包含Delay头文件
#include "LCD1602.h"	//包含LCD1602头文件
#include "MatrixKey.h"	//包含矩阵键盘头文件

unsigned int t;
unsigned int keys,cot;
void main()
{	
	LCD_Init();							//LCD初始化
	LCD_ShowString(1,1,"Input Keys :");	//LCD显示字符串
	while(1)
	{
		t=MatrixKey();				//获取矩阵键盘键码
		if(t)						//如果有按键按下
		{
			if(t<=10)
			{
				if(cot<4)
				{
					keys=keys*10;
					keys=keys+t%10;
					cot++;
				}
			    LCD_ShowNum(2,1,keys,4);//LCD显示密码
			}
				if(t==11)
				{
					if(keys==1102)
					{
						LCD_ShowString(1,14,"OK ");
						keys=0;
						cot=0;
						LCD_ShowNum(2,1,keys,4);//LCD显示密码
					}
					else
					{
						LCD_ShowString(1,14,"ERR");
						keys=0;
						cot=0;
						LCD_ShowNum(2,1,keys,4);//LCD显示密码
					}
				}
				if(t==12)
				{
					keys=0;
					cot=0;
					LCD_ShowNum(2,1,keys,4);
				}
		}
	}
}




