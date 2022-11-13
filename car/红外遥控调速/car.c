#include<reg52.h>
#include"delay.h"
#include"smg.h"
#include"key.h"
#include"time0.h"
#include"IR.h"


sbit p17=P1^7;     //两个电机
sbit p16=P1^6;     
sbit p15=P1^5;
sbit p14=P1^4;


unsigned int t,Speed,Command;
unsigned char Compare;
int main()
{    
	
	  IR_Init();
	 Timer1Init();
	while(1)
		{     
					if(IR_GetDataFlag())	//如果收到数据帧
				{
					Command=IR_GetCommand();		//获取遥控器命令码
					
					if(Command==IR_0){Speed=0;}		//根据遥控器命令码设置速度
					if(Command==IR_1){Speed=1;}
					if(Command==IR_2){Speed=2;}
					if(Command==IR_3){Speed=3;}
					
					if(Speed==0){Compare=0;}	//速度输出
					if(Speed==1){Compare=30;}
					if(Speed==2){Compare=70;}
					if(Speed==3){Compare=100;}
				}
		Nixie(7,Speed);						//数码管显示速度
				
//			p23 = 0;        //左轮正转 
//			p22 = 1;
//      p23 = 1;        //反转 
//      p22 = 0; 
//			p23 = 0;         //停止
//			p22 = 0;
//			p21 = 1;         //右轮正转
//			p20 = 0;
//			p21 = 0;         //反转
//			p20 = 1;   
//			p21 = 0;         //停止
//			p20 = 0;
   }
 }





void Timer0() interrupt 3
{
	static unsigned int i;
	TH1=0xff;           
	TL1=0xa4;  
	i++;
	i%=100;
	if(i<Compare)
	{
		
		p17 = 1;        //反转 
	  p16 = 0;   
		p15 = 0;         //反转
		p14 = 1;
	}
  else
	{
		p17 = 0;         //停止
   	p16 = 0;
		p15 = 0;         
		p14 = 0;
	}
}
