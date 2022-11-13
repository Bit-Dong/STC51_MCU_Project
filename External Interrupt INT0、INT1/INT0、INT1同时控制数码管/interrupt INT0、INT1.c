// INT0  控制第1位数码管上显示数字0
// INT1  控制第3位数码管上显示数字2
// 主函数控制第7位和第8位数码管上显示数字6、5 

# include <reg52.h>
# include <intrins.h>
# define uchar unsigned char
# define uint unsigned int
# define dig P0 

	sbit key=P3^2;    //定义外部中断负跳变引脚
  sbit key1=P3^3;
  sbit LSA=P2^2;      //74LS138 定义3个引脚对数码管进行位选
  sbit LSB=P2^3;
  sbit LSC=P2^4;
 
//阴极数码管 段选0-F
uchar code table[]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d ,0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,0x39 , 0x5e , 0x79 , 0x71};
 
//延时1s函数
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

//延时100ms函数
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void init() 
{ 
  EA = 1;	      //打开总中断允许位
  EX0 = 1;	    //打开外部中断0允许位
  IT0 = 1;	    //设定外部中断0为负跳变触发
  EX1 = 1;      //打开外部中断1允许位
  IT1 = 1;      //设定外部中断1为负跳变触发
	PX1=1;        //定义外部中断1 优先级高于 外部中断0
}
 
void main()
{
  init();
  while(1)
	{
		LSA=1,LSB=1,LSC=1;     //第8位数码管
		dig=table[5];         //在数码管上显示数字5
		Delay100ms();    
		dig=0x00;            //消隐     

		LSA=0,LSB=1,LSC=1;     //第7位数码管
		dig=table[6];         //在数码管上显示数字6
		Delay100ms();    
		dig=0x00;            //消隐   		
	}
}
 
void ex0_intr() interrupt 0 
{ 
	  Delay100ms();     //消抖
	  if(key==0)
		{
			LSA=0,LSB=0,LSC=0;     //第1位数码管
			dig=table[0];         //在数码管上显示数字0
			Delay1000ms(); 
			dig=0x00;       //消隐 
		}
}
 
void ex1_intr() interrupt 2 
{ 
	  Delay100ms();     //消抖
		if(key1==0)
		{
			LSA=0,LSB=1,LSC=0;  //第3位数码管
			dig=table[2];      //在数码管上显示数字2
			Delay1000ms();
			dig=0x00;       //消隐 
		}
}