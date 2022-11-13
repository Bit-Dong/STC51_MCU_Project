#include<reg52.h>
#include<intrins.h>
#include"delay.h"

sbit LEA=P1^0;//左边轮的使能端A
sbit LEB=P1^1;//右边轮的使能端B
//左前轮
sbit LIN3=P1^6;
sbit LIN4=P1^7;
////右前轮
sbit LIN1=P1^4;
sbit LIN2=P1^5;



//方向控制
void forward();//前进
void back();//后退
void stop();//停止
void turnLeft();//左转
void turnRight();//右转


//红外模块
//从右到左
//in4是最右边的红外灯
sbit in1=P0^1;
sbit in3=P0^2;
sbit in5=P0^3;

void trace();//红外循迹

//通过控制使能端高低电平输出的时间从而控制速度
int count=0; //用于计数
int leftpwm;   //左轮pwm  
int rightpwm;   //右轮pwm 
void time0Init();//定时器0的初始化.
       

int main()
{
		LEA=1;
    LEB=1;
    EA=1;//打开总中断
    time0Init();//定时器0初始化
    forward();//使车的方向一开始向前
    while(1)
    {
        trace();
    }
}


void forward()//前进
{
    //前进，所有轮正转
	
    LIN1=1;
    LIN2=0;

    LIN3=0;
    LIN4=1;

}
void back()//后退
{
      //前进，所有轮反转
	
    LIN1=0;
    LIN2=1;

    LIN3=1;
    LIN4=0;

}
void turnLeft()//左转
{
    //左转  左边的轮正转，右边轮反转
	
    LIN1=1;
    LIN2=0;

    LIN3=1;
    LIN4=0;

    Delay100ms();//延时5ms 控制转弯的角度

}
void turnRight()//右转
{
    //右转，左边轮反转，右边轮正转
	
    LIN1=1;
    LIN2=0;

    LIN3=1;
    LIN4=0;

    Delay100ms();//延时5ms 控制转弯的角度
}
void stop()//停止
{
    //停止，全部高电平或低电平
    LIN1=0;
    LIN2=0;

    LIN3=0;
    LIN4=0;
}

void trace()//红外循迹
{
    //当红外遇到黑线时吸收红外光，输出高电平
    //遇到白线时反射红外，输出低电平

    int dir=0;//0表示直走
                //1 代表左转
                //2 代表右转
    // 0 0 0
    if(in1==0&&in3==0&&in5==0)
        dir=0;
    // 0 0 1
    else if (in1==0&&in3==0&&in5==1)
        dir=2;
    // 0 1 0
    else if (in1==0&&in3==1&&in5==0)
        dir=0;
    // 0 1 1 
    else if (in1==0&&in3==1&&in5==1)
        dir=2;
    // 1 0 0
    else if (in1==1&&in3==0&&in5==0)
        dir=1;

    // 1 0 1
    else if (in1==1&&in3==0&&in5==1)
        dir=0;
    // 1 1 0
    else if (in1==1&&in3==1&&in5==0)
        dir=1;
    // 1 1 1
    else if (in1==1&&in3==1&&in5==1)
        dir=0;

    switch(dir)
    {
        case 0:
						leftpwm=80;
						rightpwm=40;
            forward();
            break;
        case 1:
						leftpwm=80;
						rightpwm=40;
            turnLeft();
            break;
        case 2:
						leftpwm=40;
						rightpwm=80;
            turnRight();
            break;
    }
}

void time0Init()//定时器0的初始化.
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		//工作方式一
	TL0 = 0x66;		   //定时1ms
	TH0 = 0xFC;	
	TF0 = 0;		
	TR0 = 1;          //启动定时器0
	ET0=1;            //开启定时器0的中断
}

void time0Fun() interrupt 1     //1ms 中断一次，count加一
{
    TH0=0xfc;
    TL0=0x66;
    
	count%=100;
	if(count<leftpwm)
	{
		LIN3=0;
		LIN4=1;
	}
	else
	{
		LIN3=0;
		LIN4=0;
	}
	
	if(count<rightpwm)
	{
		LIN1=1;
		LIN2=0;
	}
	else
	{
		LIN1=0;
		LIN2=0;
	}
	count++;
}