#include "sys.h"



void delay_ms(int ms)
{
	HAL_Delay(ms);
}

void delay_s(int s)
{
	HAL_Delay(s*1000);
}

