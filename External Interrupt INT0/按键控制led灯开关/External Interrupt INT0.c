//实现按键按下 开/关led灯
//外部中断0 对应按键引脚为P3^2
//外部中断1 对应按键引脚为P3^3

#include <reg52.h>

typedef unsigned char u8;
typedef unsigned int u16; 
						   

sbit key = P3^2; //定义外部中断按键引脚
sbit LED = P2^2; 

//配置外部中部中断0
void initInterrupt0()
{
	//IE0 = 1;      //IE1和IE0为状态位，即表示CPU对当前的中断执行状态，一般无需手动设置。
	              //需要设置的是寄存器位是IT0，以选择低电平信号触发还是负跳变信号触发
	EX0 = 1;
	IT0 = 1;
	EA  = 1;
}

//延迟函数
void delay(u16 i)
{
	while(i--);
}

void main()
{
	while(1)
	{
		initInterrupt0();	//调用中断
	}
}

//发生中断执行函数
void interruptHandler() interrupt 0
{
	delay(1000);  //消抖作用
	if(key==0)	//
	{
		LED = ~LED;	   //开灯/关灯
	}
}
