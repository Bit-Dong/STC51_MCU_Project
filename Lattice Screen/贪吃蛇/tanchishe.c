#include<reg52.h>					
#include<stdlib.h>					
#include<intrins.h>					
#define uchar unsigned char					
#define uint unsigned int					
#define max 20					
sbit key1=P3^1;					
sbit key2=P3^0;					
sbit key3=P3^2;					
sbit key4=P3^3;					
sbit SER=P3^4;					
sbit SLK=P3^5;					
sbit CLK=P3^6;					
sbit bee=P2^5;					
uint time=0,dir=1,flag=0;					
uint speed=30;					
uchar fdx,fdy;					
uchar line[max]=0;					
uchar column[max]=0xff;					
void delay(long a)					
{					
	for(;--a;)				
	{				
	}				
}					
void timer_Init()			                    //闹钟初始化		
{					
	TMOD=0x01;				
	TH0=(65536-50000)/256;				
	TL0=(65536-50000)%256;				
	EA=1;				
	ET0=1;				
	TR0=1;				
}					
void scan_level(uchar byte)                       //每列显示的结果					
{					
	uint i=0;				
	for(i=0;i<8;i++)				
	{				
//		SER=byte>>7;			
//		byte=byte<<1;			
		SER=byte&(0x80>>i);			
		CLK=1;			
		CLK=0;			
	}				
	SLK=1;				
	SLK=0;				
}					
void display(uchar byte,uchar column)             //显示					
{					
	scan_level(byte);				
	P0=column;				
	delay(10);				
	P0=0xff;				
}					
void Turn_rigth(uint length)                      //右移					
{ 					
	uint j;				
	if(key4==0)				
	{				
		delay(10);			
		if(key4==0)			
		{			
			if(dir!=3&&dir!=2)		
			{		
				time=0;	
				dir=2;	
				delay(5000);	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(column[0]==0xfe)	
				{	
					P0=0xff;
					while(1);
				}	
				column[0]>>=1;	
				column[0]+=0x80;	
			}		
		}			
	}				
	while(!key4);				
	delay(10);				
	while(!key4);				
}					
void Turn_down(uint length)                       //下移					
{					
	uint j;				
	if(key2==0)				
	{				
		delay(10);			
		if(key2==0)			
		{			
			if(dir!=4&&dir!=1)		
			{		
				time=0;	
				dir=1;	
				delay(5000);	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(line[0]==0x01)	
				{	
					P0=0xff;
					while(1);
				}	
				line[0]>>=1;	
			}		
		}			
	}				
	while(!key2);				
	delay(10);				
	while(!key2);				
}					
void Turn_left(uint length)                       //左移					
{					
	uint j;				
	if(key3==0)				
	{				
		delay(10);			
		if(key3==0)			
		{			
			if(dir!=2&&dir!=3)		
			{		
				time=0;	
				dir=3;	
				delay(5000);	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(column[0]==0x7f)	
				{	
					P0=0xff;
					while(1);
				}	
				column[0]<<=1;	
				column[0]+=0x01;	
			}		
		}			
	}				
	while(!key3);				
	delay(10);				
	while(!key3);				
}					
void Turn_up(uint length)                         //上移					
{					
	uint j;				
	if(key1==0)				
	{				
		delay(10);			
		if(key1==0)			
		{			
			if(dir!=1 &&dir!=4)		
			{		
				time=0;	
				dir=4;	
				delay(5000);	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(line[0]==0x80)	
				{	
					P0=0xff;
					while(1);
				}	
				line[0]<<=1;	
			}		
		}			
	}				
	while(!key1);				
	delay(10);				
	while(!key1);				
}					
void direction(uint dir,uint length)					
{					
	uint j;				
	switch(dir)				
	{				
		case 1:                     //下移			
			if(time>=speed)		
			{		
				time=0;	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(line[0]==0x01)	
				{	
					P0=0xff;
					while(1);
				}	
				line[0]>>=1;	
			}		
			break;		
		case 2:                     //右移			
			if(time>=speed)		
			{		
				time=0;	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(column[0]==0xfe)	
				{	
					P0=0xff;
					while(1);
				}	
				column[0]>>=1;	
				column[0]+=0x80;	
			}		
			break;		
		case 3:			
			if(time>=speed)		
			{		
				time=0;	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(column[0]==0x7f)	
				{	
					P0=0xff;
					while(1);
				}	
				column[0]<<=1;	
				column[0]+=0x01;	
			}		
			break;		
		case 4:			
			if(time>=speed)		
			{		
				time=0;	
				for(j=length-1;j>0;j--)	
				{	
					line[j]=line[j-1];
					column[j]=column[j-1];
				}	
				if(line[0]==0x80)	
				{	
					P0=0xff;
					while(1);
				}	
				line[0]<<=1;	
			}		
	}				
}					
void Creat_food()					
{					
	if(flag==0)				
	{				
		fdx=0x80>>rand()%8;			
		fdy=~(0x80>>rand()%8);			
		flag=1;			
	}				
}					
//void Eat_food(uint length)					
//{					
//	if((line[0]==fdx) && (column[0]==fdy))				
//	{				
//		line[length]=line[length-1];			
//		column[length]=column[length-1];			
//		length++;			
//		flag=0;			
//	}				
//}					
void die_snake(uint length)					
{					
	uint i;				
	for(i=1;i<length-1;i++)				
	{				
		if(line[0]==line[i] && column[0]==column[i])			
		{			
			P0=0xff;		
			while(1);		
		}			
	}				
}					
void main()					
{					
	uint length=2;				
	uint i;				
	uchar fd1,fd2;				
	CLK=0;				
	SLK=0;				
	bee=0;				
	timer_Init();				
	line[0]=0x40;				
	column[0]=0x7f;				
	line[1]=0x80;				
	column[1]=0x7f;				
	while(1)				
	{				
		fd1=line[length-1];			
		fd2=column[length-1];			
		Creat_food();			
		display(fdx,fdy);			
		if((line[0]==fdx) && (column[0]==fdy))			
		{			
			line[length]=line[length-1];		
			column[length]=column[length-1];		
			length++;		
			if(speed>=15)		
				speed-=2;	
			flag=0;		
		}			
		//Eat_food(length);			
		Turn_rigth(length);			
		Turn_down(length);			
		Turn_left(length);			
		Turn_up(length);			
		direction(dir,length);			
		die_snake(length);			
		for(i=0;i<length;i++)			
			display(line[i],column[i]);		
	}				
}					
void exter0() interrupt 1				//定时器0中断函数	
{					
	time++;				
	TH0=(65536-50000)/256;				
	TL0=(65536-50000)%256;				
}					
