#include <reg52.h>
#include "lcd1602.h"

#define LCD P0
sbit E = P2^7;  //使能
sbit RS = P2^6; //数据/命令（H/L）
sbit RW = P2^5; //读写（H/L）

/******延迟5毫秒函数********/
void delay5ms()   //误差 -0.000000000001us
{
    unsigned char a,b;
    for(b=15;b>0;b--)
        for(a=152;a>0;a--);
}


/******LCD1602写命令函数********/
void write_com(unsigned char command)
{
	RS = 0; 
	RW = 0; 	//高读低写
	LCD = command;
	delay5ms(); //这里延时最低要30纳秒 我们直接给5ms
	E = 1;		//使能拉高 
	delay5ms(); //最低要求延迟150纳秒 我们直接给5ms
	E = 0;
}

/******LCD1602写数据函数********/
void write_data(unsigned char dat)
{
	RS = 1;
	RW = 0;
	LCD = dat;
	delay5ms(); //这里延时最低要30纳秒 我们直接给5ms
	E = 1;		//使能拉高 
	delay5ms(); //最低要求延迟150纳秒 我们直接给5ms
	E = 0;
}
/******初始化LCD1602********/
void init_lcd()
{	
	write_com(0x06); //写入数据后光标自动右移 整屏不移动。
	write_com(0x0c); //开显示功能 无光标 不闪烁
	write_com(0x38); //数据总线8位 16X2显示 5*7点阵
	write_com(0x01); //清屏 0000 0001
	write_com(0x83); //在1602第一行第3个开始显示
}
