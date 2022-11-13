#include<intrins.h>

void Delay()		//100ms
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}
