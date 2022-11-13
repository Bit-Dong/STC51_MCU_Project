#include <REG52.H>    
#include <INTRINS.H>   
sbit speaker=P3^6; 
unsigned char timer0h,timer0l,time=1;
// 孤勇者，3分30秒，原唱4分16秒
code unsigned char gyz[]={
//122,27,121,26,122,27,121,26,122,27,121,26,120,
//// 音高（低音0，中音1，高音2），音长（节拍），音调（do,le,mi,fa,so,la,si）
//143,140,110,111,112,111,143,130,111,112,111,112,113,36,111,36,111,36,111,122,121,47,140,
////都，是勇敢的，你额头的伤口你的不同你犯的错
//143,140,111,112,111,143,140,111,112,111,112,113,36,111,36,111,36,111,123,122,47,140,
////都，不必隐藏，你破旧的玩偶你的面具你的自我
//16,111,136,116,116,115,126,116,115,116,115,116,115,143,140,16,111,136,116,116,115,116,115,137,117,117,116,127,126,143,
////他们说要带着光驯服每一头怪兽，他们说要缝好你的伤没有人爱小丑
//120,113,115,113,132,113,132,113,132,113,115,113,115,113,132,113,132,113,142,120,111,112,123,26,121,123,132,113,112,121,46,140,
////为何孤独不可光荣，人只有不完美值得歌颂，谁说污泥满身的不算英雄
116,117,211,212,117,211,221,211,117,211,212,117,211,221,211,212,213,212,213,212,223,213,212,223,225,223,
//爱你孤身走暗巷，爱你不跪的模样，爱你对峙过绝望，不肯哭一场，
116,117,211,212,117,211,221,211,117,211,212,117,211,221,211,212,213,212,213,212,223,213,212,223,225,223,225,
//爱你破烂的衣裳却敢堵命运的枪，爱你和我那么像缺口都一样
233,215,233,215,213,215,216,213,225,225,233,215,233,215,
//去吗，配吗，这褴褛的披风，战吗，战啊，
213,215,216,213,225,215,215,213,222,222,211,223,232,222,221,146,140,215,215,213,222,222,211,233,222,222,221,146,140,140,
//以最卑微的梦，致那黑夜中的呜咽与怒吼(hou)，谁说站在光里的才算英雄
116,115,136,115,116,115,116,115,126,116,115,116,115,116,115,143,140,116,115,136,115,116,115,116,115,137,117,117,116,117,116,143,140,
//他们说要戒了你的狂就像擦掉了污垢(gou)，他们说要拾台阶而上而代价是低头
113,115,113,132,113,132,113,132,113,115,113,115,113,132,113,132,113,142,120,111,112,123,126,221,223,232,213,212,231,166,120,
//那就让我不可乘风，你一样骄傲着那种孤勇，谁说对弈平凡的不算英雄

116,117,211,212,117,211,221,211,117,211,212,117,211,221,211,212,213,212,213,212,223,213,212,223,225,223,
//爱你孤身走暗巷，爱你不跪的模样，爱你对峙过绝望，不肯哭一场，
116,117,211,212,117,211,221,211,117,211,212,117,211,221,211,212,213,212,213,212,223,213,212,223,225,223,225,
//爱你破烂的衣裳却敢堵命运的枪，爱你和我那么像缺口都一样
233,215,233,215,213,215,216,213,225,225,233,215,233,215,
//去吗，配吗，这褴褛的披风，战吗，战啊，
213,215,216,213,225,215,215,213,222,222,211,223,232,222,221,146,140,215,215,213,222,222,211,233,222,222,221,146,140,140,
//以最卑微的梦，致那黑夜中的呜咽与怒吼(hou)，谁说站在光里的才算英雄

26,121,123,147,127,117,127,186,120,26,121,123,147,127,117,127,186,120,
//你的斑驳与众不同，你的沉默震耳欲聋

116,117,211,212,117,211,221,211,117,211,212,117,211,221,211,212,213,212,213,212,223,213,212,223,225,223,
//爱你孤身走暗巷，爱你不跪的模样，爱你对峙过绝望，不肯哭一场，
116,117,211,212,117,211,221,211,117,211,212,117,211,221,211,212,213,212,213,212,223,213,212,223,225,223,225,
//爱你来自于蛮荒，一生不借谁的光，你将造你的城邦，在废墟之上
233,215,233,215,213,215,216,213,225,225,233,215,233,215,
//去吗，去啊，以最卑微的梦，战吗，战啊，
213,215,216,213,225,215,215,213,222,222,211,223,232,222,221,146,140,215,215,213,222,222,211,233,222,222,221,146,140,140,
//以最孤高的梦，致那黑夜中的呜咽与怒吼(hou)，谁说站在光里的才算英雄
0 
};

// 定时时间越短，那么声音频率越高，
code unsigned char FREQH[]={
0xF2,0xF3,0xF5,0xF5,0xF6,0xF7,0xF8,
0xF9,0xF9,0xFA,0xFA,0xFB,0xFB,0xFC,
0xFC,0xFC,0xFD,0xFD,0xFD,0xFD,0xFE,
0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,
} ;
code unsigned char FREQL[]={
0x42,0xC1,0x17,0xB6,0xD0,0xD1,0xB6,
0x21,0xE1,0x8C,0xD8,0x68,0xE9,0x5B,
0x8F,0xEE,0x44,0x6B,0xB4,0xF4,0x2D,
0x47,0x77,0xA2,0xB6,0xDA,0xFA,0x16,
};

//做成对应的频率表，其实前几个很少遇得到，那么这里再缩减的话，
//就除以10，就可以用char类型而不用int类型了，后边计算计时时间的时候再乘10补回
unsigned int  code FreTab[28]  = {
3517,3134,2792,2633,2351,2094,1865,
1758,1566,1395,1319,1175,1046,932 ,
880 ,785 ,699 ,660 ,587 ,523 ,466 ,
440 ,392 ,349 ,329 ,293 ,261 ,233 ,  
};

void t0int() interrupt 1
{
	speaker=!speaker;
	TH0=timer0h;
	TL0=timer0l;
}

//  节奏的快慢，这里是半个节拍的时间
void delay(unsigned char t)
{
	unsigned long t2;
	for(;t>0;t--)
	{
		for(t2=0;t2<5000;t2++){;}
	}
	TR0=0;// 停止发音	如果屏蔽掉，会出现连音的不正常现象
}
/**/
void song()
{
	unsigned char k=0;
	unsigned long i=0;	//  由于歌词长度问题，需要设置大一点的范围，否则还没唱完一遍又重新开始了
	// 这里这样做就只唱一遍，寻到最后的0值时就停止了
	while(time)	
	{
		if(gyz[i]%10==0) 	 // 音调为0值时停顿处理
		{
			TR0=0;	  // 停止发音
		}
		else
		{
			k=gyz[i]%10+7*(gyz[i]/100+1)-1;
			timer0h=FREQH[k];				// 这里将K值改成定值，发现实际上并不是按照do,le,mi,fa,so,la,si这样发音
			timer0l=FREQL[k];
			//如果用频率表输出的话，就屏蔽上两句，开启下两句
			//timer0h=(65535-FreTab[k])/256;
			//timer0l=(65535-FreTab[k])%256;
			TR0=1;	  // 启动T0输出方波去发音
		}
		time=gyz[i]/10%10;
		i=i+1;
		
		delay(time);
	}
}
void main(void)
{
	TMOD=1;		// 设置定时器0为16位计数模式 
	EA=1;ET0=1;	// 开定时器0中断
	while(1)
	{
		song();
	}
}
