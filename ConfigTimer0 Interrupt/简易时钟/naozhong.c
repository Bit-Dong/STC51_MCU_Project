#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define dig P0
  sbit beep=P2^5;
  sbit LSA=P2^2;      //74LS138 定义3个引脚对数码管进行位选
  sbit LSB=P2^3;
  sbit LSC=P2^4;

//void Delay100us()		//@11.0592MHz
//{
//	unsigned char i;

//	_nop_();
//	i = 43;
//	while (--i);
//}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}


void Delay1us()		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}

 
//阴极数码管 段选0-F
uchar code smg[]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d ,0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,0x39 , 0x5e , 0x79 , 0x71};

void Timer0Init(void)		//1ms
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0x66;		
	TH0 = 0xFC;	
	TF0 = 0;		
	TR0 = 1;
	EA=1;
	ET0=1;
}

unsigned long o=50000;
unsigned int i;
uchar count1=0,count2=0,count3=0,count4=0,count5=0,count6=0;
void main()
{
	Timer0Init();    
//	if(count2==6)
//			{	
//					while(o--)
//				{
//							beep=~beep;
//							Delay10us();
//					}
//				}
	while(1)
	{										

	    	LSA=0;LSB=0;LSC=0;
				dig=smg[count1];
				Delay1us();dig=0x00;    //使动态数码管消隐
		
				LSA=1;LSB=0;LSC=0;
				dig=smg[count2];
				Delay1us();dig=0x00;    //使动态数码管消隐
		
			  LSA=0;LSB=1;LSC=0;
				dig=0x40;
				Delay1us();dig=0x00;    //使动态数码管消隐 
		
				LSA=1;LSB=1;LSC=0;
				dig=smg[count3];
				Delay1us();dig=0x00;    //使动态数码管消隐
		
				LSA=0;LSB=0;LSC=1;
				dig=smg[count4];
				Delay1us();dig=0x00;    //使动态数码管消隐
				
				LSA=1;LSB=0;LSC=1;
				dig=0x40;
				Delay1us();dig=0x00;    //使动态数码管消隐
				
   		  LSA=0;LSB=1;LSC=1;
				dig=smg[count5];
				Delay1us();dig=0x00;    //使动态数码管消隐
				
				LSA=1;LSB=1;LSC=1;
				dig=smg[count6];
				Delay1us();dig=0x00;    //使动态数码管消隐
	   
	}
}


unsigned char t=0;
void naozhong() interrupt 1
{

	i++;
	if(i%1000==0)
		{
			count1++;
			
			if(count1==10)
			{
				count2=count2+count1/10;
				count1=0;
			}

			if(count2==6)
			{	
//					while(o--)
//				{
//							beep=~beep;
//							Delay10us();
//					}
				count3=count3+count2/6;
				count2=0;
				count1=0;
			}
			
				if(count3==10)
			{
				count4=count4+count3/10;
				count3=0;
				count2=0;
				count1=0;
			}
			
				if(count4==6)
			{
				count5=count5+count4/6;
				count4=0;
				count3=0;
				count2=0;
				count1=0;
			}
			
			if(count5==4)
			{
				t++;
			}
			
				if(count5==10)
			{
				count6=count6+count5/10;
				count5=0;
				count4=0;
				count3=0;
				count2=0;
				count1=0;
			}
			
			if(t==3)
			{
				count6=0;
				count5=0;
				count4=0;
				count3=0;
				count2=0;
				count1=0;
				t=0;
			}
			
		}

		TL0 = 0x66;		
	  TH0 = 0xFC;	
}
	