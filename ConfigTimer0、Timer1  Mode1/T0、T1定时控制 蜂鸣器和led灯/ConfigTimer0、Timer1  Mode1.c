// 定时器0控制 蜂鸣器发出声音
// 定时器1控制 led灯亮灭

#include<reg52.h>
#include<intrins.h>

sbit led=P2^0;
sbit beep=P1^5;

unsigned char T0RH,T0RL;
unsigned char T1RH,T1RL;

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



void ConfigTimer0(unsigned char ms)     //1<=ms<=71
{
	unsigned long tmp;
	tmp=11059200/12;                    //计算频率
	tmp=(tmp*ms)/1000;
	tmp=65536-tmp;                 //初值
	
	T0RH=(unsigned char)(tmp>>8);
	T0RL=(unsigned char)(tmp);
	TMOD &=0xf0;       //防止影响定时器T1的高四位
	TMOD |=0x01;
	TH0=T0RH;              //设置定时时间
	TL0=T0RL;  
	TR0=1;                 //启动定时器0
}

void ConfigTimer1(unsigned char ms)
{
	unsigned long tmp;
	tmp=11059200/12;
	tmp=(tmp*ms)/1000;
	tmp=65536-tmp;
	
	T1RH=(unsigned char)(tmp>>8);
	T1RL=(unsigned char)(tmp);
	TMOD &=0x0f;
	TMOD |=0x10;
	TH1=T1RH;
	TL1=T1RL;
	TR1=1;
}

void main()
{
	unsigned int cnt;
	ConfigTimer0(2);          //设定2ms
	ConfigTimer1(4);          //设定4ms
	while(1)
	{                     //轮询模式
		if(TF0==1)
		{
			TF0=0;               //软件清零
			TH0=T0RH;             //重新赋值
	    TL0=T0RL;
			
			cnt=60000;
			while(cnt--)
			{
				beep=~beep;     //蜂鸣器翻转状态
        Delay1ms();	    //定义100ms时 “滴滴” 的声音，1ms时 “嗯~ ~” 的声音
			}
		}
		if(TF1==1)
		{
			TF1=0;
	    TH1=T1RH;
	    TL1=T1RL;	
      led=~led;            //led灯翻转状态
		}
	}
}	
	