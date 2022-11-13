#include<reg52.h>
sbit led=P2^0;
sbit k3=P3^2;
sbit beep=P2^5;
void delay()
{
    unsigned char a,b;
	for(a=0;a<200;a++)
	for(b=0;b<200;b++);
}
//void Int0()
//{
//	IT0=1;
//	EX0=1;
//	EA=1;
//}
void main()
{
	//Int0();
	while(1)
		{
			beep=~beep;
			delay();
		}
}

//void ledxs() interrupt 0
//{
//	delay();
//		if(k3==0)
//		{
//		beep=~beep;
//		}
//}


