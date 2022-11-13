// T0定时控制 led灯亮灭 和 蜂鸣器发出声音

#include<reg52.h>
#include<intrins.h>

sbit led=P2^0;
sbit beep=P1^5;

unsigned char T0RH,T0RL;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void ConfigTimer0(unsigned char ms)      //1<=ms<=71
{
	unsigned long tmp;
	tmp=11059200/12;             //计算频率
	tmp=(tmp*ms)/1000;
	tmp=65536-tmp;
	T0RH=(unsigned char)(tmp>>8);
	T0RL=(unsigned char)(tmp);
	
	TMOD &=0xf0;  //配置工作模式 
	TMOD |=0x01;
	TH0=T0RH;       //设置定时器时间
	TL0=T0RL;      
	TR0=1;         //启动定时器
}

void main()
{
	unsigned int cnt=0;
	ConfigTimer0(1);
	while(1)
	{
		if(TF0==1)       //增到0xffff溢出 
		{
			cnt++;
			TF0=0;            //软件清零
			TH0=T0RH;
	    TL0=T0RL;       //重新赋值
			led=~led;
			if(cnt>=100)
			{
			cnt=0;
			beep=~beep; 
			//Delay1ms();     //定与不定义这个延时1ms 蜂鸣器“滴滴” 声 感觉都差不多  led视觉上一直亮
			Delay1000ms();    //定义延时1000ms 蜂鸣器“滴滴" 声明显变慢 且led灯 一闪一闪 
			}
			
		}
	}
}