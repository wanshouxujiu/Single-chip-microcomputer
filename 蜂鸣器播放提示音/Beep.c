#include <REGX52.H>
#include "another.h"

sbit Beep = P1^5;

void Beep_Time(unsigned int ms)
{
	unsigned int i = 0;
	for(i = 0; i < ms; i++)
	{
		Beep = !Beep;
		Delay(1);
	}
}
