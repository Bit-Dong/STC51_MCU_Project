  //运用定时器1的模式二 自动重装式
  //SCON的方式一
#include <reg52.h>

/**
  * @brief  串口初始化，4800bps@12.000MHz
  * @param  无
  * @retval 无
  */
void UART_Init()
{
	SCON=0x40;      
                    	//   B7     B6     B5     B4     B3     B2     B1     B0
	                    // SM0/FE   SM1    SM2    REN    TB8    RB8    TI     RI
	
	PCON |= 0x80;
	                    //   B7     B6     B5     B4     B3     B2     B1     B0
	                    //  SMOD   SMOD0   --     POF   GF1    GF0     PD     IDL
 	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;	
                        //GATE   C/T'  M1  M0  GATE   C/T'  M1  M0
	
	           //TCOD:
	                    //   B7     B6     B5     B4     B3     B2     B1     B0
	                    //   TF1    TR1    TF0    TR0    IE1    IT1    IE0    IT0
	                    
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}
       
/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;     //就启动串行通信的发送
	while(TI==0);       // TI:发送中断请求标志位  需软件复位
	TI=0;               // RI:接受中断请求标志位  需软件复位
}


