#include<reg52.h>

#define led P1

void Timer0_Init(void)
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

void delay(unsigned int i)
{
	while(i--);
}

unsigned char Counter,Compare;	//计数值和比较值，用于输出PWM

void main()
{

	Timer0_Init();
	Compare=50;
	while(1)
	{
		for(Compare=100;Compare>0;Compare--)
		{
				
		}
		for(Compare=0;Compare<100;Compare++)
		{
				
		}
}
	}
	unsigned char i;
void Timer0_Routine() interrupt 1
{
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	Counter++;
	Counter%=100;	//计数值变化范围限制在0~99
	for(i=0;i<8;i++)
	{
	if(Counter<Compare)	//计数值小于比较值
	{
		led=~(0x01>>i);		//输出1
	}
	else				//计数值大于比较值
	{
		led=0;		//输出0
	}
  }
}
