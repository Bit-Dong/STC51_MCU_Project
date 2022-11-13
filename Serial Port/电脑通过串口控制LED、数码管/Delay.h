#ifndef __DELAY_H__
#define __DELAY_H__

  sbit LSA=P2^2;      //74LS138 定义3个引脚对数码管进行位选
  sbit LSB=P2^3;
  sbit LSC=P2^4;

void Delay(unsigned int xms);

#endif
