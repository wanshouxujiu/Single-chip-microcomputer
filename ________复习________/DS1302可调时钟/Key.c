#include <REGX52.H>
#include "Delay.H"


unsigned char Key()
{
	if(P3_1 == 0){Delay(15);while(~P3_1)Delay(15);return 1;}
	if(P3_0 == 0){Delay(15);while(~P3_0)Delay(15);return 2;}
	if(P3_2 == 0){Delay(15);while(~P3_2)Delay(15);return 3;}
	if(P3_3 == 0){Delay(15);while(~P3_3)Delay(15);return 4;}
	return 0;
}