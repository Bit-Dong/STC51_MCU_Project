#include <reg52.h>
#include "Delay.h"
sbit led=P2^0;
void main()
{
	while(1)
	{
		Delay();
		led=~led;
	}
}