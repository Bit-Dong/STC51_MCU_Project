//T0中断控制led灯定时翻转
 
#include <reg52.h>		 
 
typedef unsigned int u16;	  
typedef unsigned char u8;
unsigned char T0RH,T0RL;
sbit led=P2^0;	 

void Timer0Init(u8 ms)
{
	unsigned long tmp;
	tmp=11059200/12;
	tmp=(tmp*ms)/1000;
	tmp=65536-tmp;                 //初值
	T0RH=(unsigned char)(tmp>>8);
	T0RL=(unsigned char)(tmp);
	
	TMOD &=0xf0;       //防止影响定时器T1的高四位
	TMOD |=0x01;
	TH0=T0RH;           //设置定时时间
	TL0=T0RL;                   
 
	ET0=1;       //打开T0中断允许位
	EA=1;        //打开总中断允许位开关
	TR0=1;       //启动定时器0
}
 
void main()
{	
	Timer0Init(1);  
	while(1);		
}

void Timer0() interrupt 1
{
	static u16 i;
	TH0=T0RH;           //重新赋值定时时间
	TL0=T0RL;  
	i++;
	if(i==100)
	{
		i=0;
		led=~led;	
	}	
}