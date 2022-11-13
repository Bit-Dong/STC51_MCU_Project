#include <reg52.h>
#include "Delay.h"
 
//定义74HC595三个引脚   74HC595是串行输入并行输出的移位寄存器
sbit RCK=P3^5;		//RCLK      上升沿锁存，移位完成后 给一个上升沿 将数据并行输出
sbit SCK=P3^6;		//SRCLK     上升沿移位，
sbit SER=P3^4;		//SER       不为0时，串行数据，给移位寄存器输入 (串行输入)

#define Lattic P0     //P0控制点阵的列 需要一列一列的扫描 

void _74HC595_WriteByte(unsigned char Byte)      //74HC595写入一个字节
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);   
		SCK=1;     //给一个上升沿，向下移位
		SCK=0;     //恢复低电平
	}
	RCK=1;       //给一个上升沿，输出数据
	RCK=0;       //恢复低电平
}


/**
  * @brief  LED点阵屏显示一列数据
  * @param  Column 要选择的列，范围：0~7，0在最左边
  * @param  Data 选择列显示的数据，高位在上，1为亮，0为灭
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74HC595_WriteByte(Data);           //点阵led灯1为亮，0为灭
	Lattic =~(0x80>>Column);
	Delay(1);
	Lattic=0xFF;
}

void main()
{
	SCK=0;
	RCK=0;
	while(1)
	{
	
		MatrixLED_ShowColumn(0,0x3C);
		MatrixLED_ShowColumn(1,0x42);
		MatrixLED_ShowColumn(2,0xA9);
		MatrixLED_ShowColumn(3,0x85);
		MatrixLED_ShowColumn(4,0x85);
		MatrixLED_ShowColumn(5,0xA9);
		MatrixLED_ShowColumn(6,0x42);
		MatrixLED_ShowColumn(7,0x3C);
	}
}

