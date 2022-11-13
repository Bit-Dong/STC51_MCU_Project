// Mode3的两个定时器分别定时控制 两led灯状态翻转

#include<reg52.h>
                      //Mode3 只适用于定时器T0  双8bit定时器 分成了两个定时器TL0、TH0
sbit led0=P2^0;
sbit led1=P2^1;
unsigned char T0RH,T0RL;

void ConfigTimer0Mode3(unsigned int usL,unsigned int usH)      //1<=us<=268us  微妙
{
	unsigned long tmp;
	if(usL>267)
		usL=267;
	if(usH>267)
		usH=267;
//配置第一个定时器
	tmp=11059200/12;
	tmp=(tmp*usL)/1000000;
	tmp=256-tmp;             //初值
	T0RL=tmp;
//配置第二个定时器
	tmp=11059200/12;
	tmp=(tmp*usH)/1000000;
	tmp=256-tmp;
	T0RH=tmp;
	
	TMOD &=0xf0;         //防止影响定时器T1的高四位
	TMOD |=0x03;
	TL0=T0RL;           //设定定时时间
	TH0=T0RH;
	TR0=1;             //启动第一个定时器
	TR1=1;              //启动第二个定时器
}

void main()
{
	unsigned int cntL,cntH;
	ConfigTimer0Mode3(200,100);        //各设定200us、100us
	while(1)
	{
		if(TF0==1)
		{
			cntL++;
			if(cntL>=5000)               //5000*200=1000000us=1s
			{
				cntL=0;
				led0=~led0;
			}
			TF0=0;
			TL0=T0RL;
		}
		if(TF1==1)
		{
			cntH++;
			if(cntH>=5000)            //5000*100=500000us=0.5s
			{
				cntH=0;
				led1=~led1;
			}
			TF1=0;
			TH0=T0RH;
		}
	}
}
