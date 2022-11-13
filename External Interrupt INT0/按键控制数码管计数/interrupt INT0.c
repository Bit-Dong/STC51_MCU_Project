//按键与INT0引脚相连，按下按键触发外部中断
//每触发一次外部中断计数加1，并将次数显示在数码管上 
// 100次一个循环 100时置零


#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define dig P0
	sbit key=P3^2;    //定义外部中断0 负跳变引脚
  sbit LSA=P2^2;      //74LS138 定义3个引脚对数码管进行位选
  sbit LSB=P2^3;
  sbit LSC=P2^4;
 
//阴极数码管 段选0-F
uchar code smg[]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d ,0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,0x39 , 0x5e , 0x79 , 0x71};

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


//初始化外部中断0
void initEx0()
{
  EA  = 1;	 //打开总中断开关
  EX0 = 1;	 //外部中断0允许位
  IT0 = 1;	 //外部中断0负跳变触发
}
 
 
uchar  count1=0,count = 0;    //计数变量
 
void main()
{
	
  initEx0();
  while(1)
		{
			if(count<10)
			{
				if((count1!=0)&&(count1!=10))
				{
					LSA=1,LSB=1,LSC=0;
					dig=smg[count];        //在数码管上显示中断次数
					Delay1ms(); dig=0x00;
					
					LSA=0,LSB=0,LSC=1;
					dig=smg[count1];       //在数码管上显示中断次数
					Delay1ms(); dig=0x00;
				}
				else
				{					
					LSA=1,LSB=1,LSC=0;
					dig=smg[count];   //在数码管上显示中断次数
					Delay1ms(); dig=0x00;
				}
			}
			if((count>9)&&(count<100))
			{
				count1=count1+count/10;
				count  %=10;
				LSA=1,LSB=1,LSC=0;
        dig=smg[count];        //在数码管上显示中断次数
				Delay1ms(); dig=0x00;
				
				LSA=0,LSB=0,LSC=1;
        dig=smg[count1];       //在数码管上显示中断次数
				Delay1ms(); dig=0x00;
			}
		}
}
 
	 void ex0_intr() interrupt 0 
	{ 
		Delay1ms();   //消抖
		if(key==0)
		{
			count=count+1;   //每进入一次中断 次数+1
	  }
		if((count1==10)|(count==100))
		{
			count1=0;
			count=0;
		}
	}