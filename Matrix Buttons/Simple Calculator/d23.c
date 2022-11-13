/*    简单计算器:

                       4x4矩阵按键分布
                      0    1    2    3
                      4    5    6    7
                      8    9    +    -
                      *    /   RES   =
*/

#include<reg52.h>
#define key P1   //定义key为矩阵按键P1口
#define dig P0   //定义dig为数码管P0口
typedef unsigned char u8;
typedef unsigned int u16;
sbit LSA=P2^2;  //74LS138位选
sbit LSB=P2^3;
sbit LSC=P2^4;
u16 keyvalue;  //存键值
u16 keyswitch; //判断是否按下按键
u8 code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   //段选0-F
u16 box[8]={0};
u16 i;

//延迟函数
void delay(u16 i)
{
	while(i--);
}

//输出函数(把值显示在数码管上)
void display()
{
	LSA=0;LSB=0;LSC=0;
	dig=duanxuan[box[0]];
	delay(50);dig=0x00;    //使动态数码管消隐
	
	LSA=1;LSB=0;LSC=0;
	dig=duanxuan[box[1]];
	delay(50);dig=0x00;    //使动态数码管消隐
	
	LSA=0;LSB=1;LSC=0;
	dig=duanxuan[box[2]];
	delay(50);dig=0x00;    //使动态数码管消隐
	
	LSA=1;LSB=1;LSC=0;
	dig=duanxuan[box[3]];
	delay(50);dig=0x00;    //使动态数码管消隐
	
	LSA=0;LSB=0;LSC=1;
	dig=duanxuan[box[4]];
	delay(50);dig=0x00;    //使动态数码管消隐
	
	LSA=1;LSB=0;LSC=1;
	dig=duanxuan[box[5]];
	delay(50);dig=0x00;    //使动态数码管消隐
	
	LSA=0;LSB=1;LSC=1;
	dig=duanxuan[box[6]];
	delay(50);dig=0x00;    //使动态数码管消隐
	
	LSA=1;LSB=1;LSC=1;
	dig=duanxuan[box[7]];
	delay(50);dig=0x00;    //使动态数码管消隐
}

//扫码函数(扫描矩阵按键)
void keydown()
{
	u16 a=0;
	key=0x0f;
	if(key!=0x0f)
	{
		delay(1000);
		if(key!=0x0f)
		{
			key=0x0f;
			switch(key)
			{
				case 0x07 : keyvalue=0;break;
				case 0x0b : keyvalue=1;break;
				case 0x0d : keyvalue=2;break;
				case 0x0e : keyvalue=3;break;
			}
			key=0xf0;
			switch(key)
			{
				case 0x70 : keyvalue=keyvalue;break;
				case 0xb0 : keyvalue=keyvalue+4;break;
				case 0xd0 : keyvalue=keyvalue+8;break;
				case 0xe0 : keyvalue=keyvalue+12;break;
			}
			if((keyvalue>=0)&&(keyvalue<=9))
			{
				keyswitch=1;
			}
			while((a<100)&&(key!=0xf0))
			{
				delay(1000);
				a++;
			}
		}
	}
}

//主函数
void main()
{
	unsigned long  a=0,b=0,c=0;
	while(1)
	{
		display();
		
		keydown();
		if(keyswitch==1)  
		{
			for(i=7;i>0;i--)
			{
				box[i]=box[i-1];       //使按键输入的数字从左至右显示在数码管上
			}
			box[0]=keyvalue;
			keyswitch=0;
		}
		else if(keyvalue==14)      //按键14为清零键
		{
			for(i=0;i<8;i++)
			   box[i]=0;
			display();
		}
		else if(keyvalue==10)      //按键10为加号‘+’
		{
			a=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                //使按下的第一个数的值存入a；
			for(i=0;i<8;i++)
			   box[i]=0;
			while(1)
			{
				display();
				keydown();
				if(keyswitch==1)
				{
					for(i=7;i>0;i--)
					{
						box[i]=box[i-1];
					}
					box[0]=keyvalue;
					keyswitch=0;
				}
				if(keyvalue==15)    //按键15为等于符号'='
					break;   
			}
			b=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                 //使按下的第二个数的值存入b；
			c=a+b;
			box[0]=c%10;
			box[1]=c/10%10;
			box[2]=c/100%10;
			box[3]=c/1000%10;
			box[4]=c/10000%10;
			box[5]=c/100000%10;
			box[6]=c/1000000%10;
			box[7]=c/10000000%10;
			display();
		}
		else if(keyvalue==11)      //按键11为加号‘-’
		{
			a=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                //使按下的第一个数的值存入a；
			for(i=0;i<8;i++)
			   box[i]=0;
			while(1)
			{
				display();
				keydown();
				if(keyswitch==1)
				{
					for(i=7;i>0;i--)
					{
						box[i]=box[i-1];
					}
					box[0]=keyvalue;
					keyswitch=0;
				}
				if(keyvalue==15)    //按键15为等于符号'='
					break;   
			}
			b=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                 //使按下的第二个数的值存入b；
			c=a-b;
			box[0]=c%10;
			box[1]=c/10%10;
			box[2]=c/100%10;
			box[3]=c/1000%10;
			box[4]=c/10000%10;
			box[5]=c/100000%10;
			box[6]=c/1000000%10;
			box[7]=c/10000000%10;
			display();
		}
		else if(keyvalue==12)      //按键12为加号‘*’
		{
			a=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                //使按下的第一个数的值存入a；
			for(i=0;i<8;i++)
			   box[i]=0;
			while(1)
			{
				display();
				keydown();
				if(keyswitch==1)
				{
					for(i=7;i>0;i--)
					{
						box[i]=box[i-1];
					}
					box[0]=keyvalue;
					keyswitch=0;
				}
				if(keyvalue==15)    //按键15为等于符号'='
					break;   
			}
			b=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                 //使按下的第二个数的值存入b；
			c=a*b;
			box[0]=c%10;
			box[1]=c/10%10;
			box[2]=c/100%10;
			box[3]=c/1000%10;
			box[4]=c/10000%10;
			box[5]=c/100000%10;
			box[6]=c/1000000%10;
			box[7]=c/10000000%10;
			display();
		}
		else if(keyvalue==13)      //按键13为加号‘/’
		{
			a=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                //使按下的第一个数的值存入a；
			for(i=0;i<8;i++)
			   box[i]=0;
			while(1)
			{
				display();
				keydown();
				if(keyswitch==1)
				{
					for(i=7;i>0;i--)
					{
						box[i]=box[i-1];
					}
					box[0]=keyvalue;
					keyswitch=0;
				}
				if(keyvalue==15)    //按键15为等于符号'='
					break;   
			}
			b=box[0]+box[1]*10+box[2]*100+box[3]*1000+box[4]*10000+box[5]*100000+box[6]*1000000+box[7]*10000000;
			                 //使按下的第二个数的值存入b；
			c=a/b;
			box[0]=c%10;
			box[1]=c/10%10;
			box[2]=c/100%10;
			box[3]=c/1000%10;
			box[4]=c/10000%10;
			box[5]=c/100000%10;
			box[6]=c/1000000%10;
			box[7]=c/10000000%10;
			display();
		}
	}
}