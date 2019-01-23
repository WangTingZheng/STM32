#include "keypad.h"
#include "oled.h"
#include "delay.h"


void test_key(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==Bit_RESET)
	{
		OLED_ShowNum(0,0,17,2,16);
	}
	else
	{
		OLED_ShowNum(0,0,18,2,16);
	}
}

//不按下 4口为SET，按下为RESET
