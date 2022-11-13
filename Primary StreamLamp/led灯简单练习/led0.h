#ifndef __LED_H_
#define __LED_H_

#define led P1
sbit key2=P3^2;
sbit key3=P3^3;
sbit led1=P1^0;
sbit led2=P1^1;
sbit led7=P1^6;
sbit led8=P1^7;

void zhuanxiang();
void liushuideng();
void chuanglian();
void shanshuo();
void danhshudengliang();
void jiafa();

#endif
