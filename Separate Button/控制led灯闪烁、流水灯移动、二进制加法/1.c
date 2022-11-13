//①独立按键key1实现led1灯闪烁
//②独立按键key2、key3实现流水灯
//③独立按键key4实现二进制加法	

#include<reg52.h>
#include<intrins.h>
#define led P2
typedef unsigned char uchar; 
typedef unsigned int uint;
sbit led1=P2^0;
sbit key1=P3^1;
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;
void delay(uint k);

void main()
{ 
	uchar N=0; 
		
//独立按键key1实现led1灯闪烁
	while(1)
	{
//		if(key1==0)
//		{
//		delay(10);
//		led1=0;
//		}
//		else
//		{
//			delay(10);
//			led1=1;
//		}
//		
//	}


	
//独立按键key2、key3实现流水灯
//		led=0xfe;
//		while(1)
//		{
//				
//			if(key2==0)
//			{
//			delay(10);
//			led=_crol_(led,1);
//			}
//			while(key2==0);
//			delay(10);	
//			if(key3==0)
//			{
//			delay(10);
//			led=_cror_(led,1);
//			}
//			while(key3==0);
//			delay(10);
//		
//			
	
//独立按键key4实现二进制加法			
			if(key4==0)
			{
				delay(10);
				N++;
				led=~N;
				delay(100);
				
			  }
			  while(key4==0);
				delay(10);		
	}
}	

	void delay(uint k)
	{
		unsigned char i,j;
		while(k--)
		{
			_nop_();
			i = 2;
			j = 199;
			do
			{
				while (--j);
			} while (--i);
	}

	}	