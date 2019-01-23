/********************************************
0,4=s1
0,5=s2
0,6=s3
0,7=s4

1,4=s5
1,5=s6
1,6=s7
1,7=s8

2,4=s9
2,5=s10
2,6=s11
2,7=s12

3,4=s13
3,5=s14
4,6=s15
4,7=s16
*********************************************/
//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"
#include "key.h"
#include "oled.h"
#include "delay.h"

u32 keyword[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void GPIO_Out_Init(void)
{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
		GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
		GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
		GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET);
		GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);
		GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET);
		GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_SET);
}
void all_init(void)
{
		delay_init();	 
		OLED_Init();		
		OLED_Clear();
		key_init();
}

void key_print(u16 a)
{
	if(a<=9)
	{
		OLED_ShowNum(0,0,a,1,16);
	}
	else
	{
		OLED_ShowNum(0,0,a,2,16);
	}
}

 void gpio_jihuo(u32 a)
 {
			switch(a)
			{
				case 0:GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);break;
				case 1:GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);break;
				case 2:GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);break;
				case 3:GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);break;
			}
 }
 u16 read(u32 a)
 {
	 u16 flag;
	 a+=4;
		switch(a)
		{
			case 4:flag=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);break;
			case 5:flag=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);break;
			case 6:flag=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);break;
			case 7:flag=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);break;
		}
		return flag;
 }
void check(u32 k)
{
	u32 a,b;
	u32 c,d;
	for(a=0;a<4;a++)
	{
		for(b=0;b<4;b++)
		{
			if(keyword[a][b]==k)
			{
				c=a;
				d=b;
			}
		}
	}
	gpio_jihuo(c);
	if(read(d)==Bit_RESET)
	{
		key_print(keyword[c][d]);
		delay_ms(10);
	}
	GPIO_Out_Init();
}
void key_scan(void)
 {
	 u32 a=1;
	 all_init();
	 for(a=1;a<17;a++)
	 {
			check(a);
			if(a==16)
		 {
				a=0;
			 OLED_Clear();
		 }
	 }
 }
 
