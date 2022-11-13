// T0 定时控制led灯状态翻转

#include<reg52.h>       
                         //Mode2 自动重装载  TL0 8bit
sbit led=P2^0;

void ConfigTime0Mode2(unsigned char us)     //1<=us<=268us 微妙
{
	unsigned long tmp;
	if(us>267)
		us=267;
	tmp=11059200/12;
	tmp=(tmp*us)/1000000;
	tmp=256-tmp;
	TL0=tmp;          //TL0增到0xff后溢出 TH0自动补上
	TH0=tmp;
	
	TMOD &=0xf0;       //防止工作时影响定时器T1的高四位
	TMOD |=0x02;
	TR0=1;            //启动定时器T0
}

void main()
{
	unsigned int cnt;
	ConfigTime0Mode2(200);      //设定200us 微妙
	while(1)
	{
		if(TF0==1)        //溢出
		{
			cnt++;
			if(cnt>=5000)           //5000*200=1000000us=1s  
			{
				cnt=0;
				led=~led; 
			}
			TF0=0;                   //软件清零
		}
	}
}
