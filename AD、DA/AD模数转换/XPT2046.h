#ifndef __XPT2046_H__
#define __XPT2046_H__

#define XPT2046_VBAT	0xAC            //AIN2，光敏电阻  
#define XPT2046_AUX		0xEC
#define XPT2046_XP		0x9C	//0xBC    //AIN0，可调电阻
#define XPT2046_YP		0xDC            //AIN1，热敏电阻 

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif
