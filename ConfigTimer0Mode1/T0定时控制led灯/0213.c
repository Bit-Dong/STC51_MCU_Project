#include<reg52.h>
sbit led0=P2^0;
void main()
{
	unsigned int cnt=0;
	TMOD &=0xf0;
	TMOD |=0x01;  //设置特殊功能寄存器TMOD，配置好工作模式
	TH0=0xfc;    //设置定时时间
	TL0=0x6e;
	TR0=1;        //启动打开定时器
	
	while(1)
	{
		if(TF0==1)
		{
			TF0=0;      //软件清零
			TH0=0xfc;   //重新赋值
	    TL0=0x6e;
			cnt++;
			if(cnt>=500)
			{
				cnt=0;
				led0=~led0;
			}
		}
	}
}