/********************************************
8	PA0    s1  s2  s3  s4
7	PA2		 s5  s6  s7  s8
6	PA4		 s9  s10 s11 s12
5	PA6		 s13 s14 s15 s16
4	PA1
3	PA3
2	PA5
1	PA7
*********************************************/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "key.h"
#include "oled.h"
#include "delay.h"

u16 value_out=1;
u16 value_in=1;
u16 bin_out[4]={0};
u16 bin_in[4]={0};

void all_init(void)
{
		delay_init();
		NVIC_Configuration(); 	 
		OLED_Init();		
		OLED_Clear();
}
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
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
void zhuanghua(u16 a)
{
	if(a==1)//输出模式+10进制到2进制
	{
		bin_out[0]=value_out/8;
		bin_out[1]=(value_out-bin_out[0]*8)/4;
		bin_out[2]=(value_out-bin_out[0]*8-bin_out[1]*4)/2;
		bin_out[3]=value_out-value_out-bin_out[0]*8-bin_out[1]*4-bin_out[2]*2;
	}
	if(a==2)//输出模式+2进制到10进制
	{
		value_out=bin_out[0]*8+bin_out[1]*4+bin_out[2]*2+bin_out[1];
	}
	if(a==3)//输入模式+10进制到2进制
	{
		bin_in[0]=value_in/8;
		bin_in[1]=(value_in-bin_in[0]*8)/4;
		bin_in[2]=(value_in-bin_in[0]*8-bin_in[1]*4)/2;
		bin_in[3]=value_in-value_in-bin_in[0]*8-bin_in[1]*4-bin_in[2]*2;
	}
	if(a==4)//输入模式+2进制到10进制
	{
		value_in=bin_in[0]*8+bin_in[1]*4+bin_in[2]*2+bin_in[1];
	}
}
void key_choice()
{
	zhuanghua(1);
	switch(bin_out[0])
	{
		case 1:GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);break;
		case 0:GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);break;
	}
	switch(bin_out[1])
	{
		case 1:GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);break;
		case 0:GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);break;
	}
	switch(bin_out[2])
	{
		case 1:GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);break;
		case 0:GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);break;
	}
	switch(bin_out[3])
	{
		case 1:GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);break;
		case 0:GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);break;
	}
}
void key_ask()
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==Bit_SET)
	{
		bin_in[0]=1;
	}
	else
	{
		bin_in[0]=0;
	}
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==Bit_SET)
	{
		bin_in[1]=1;
	}
	else
	{
		bin_in[1]=0;
	}
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==Bit_SET)
	{
		bin_in[2]=1;
	}
	else
	{
		bin_in[2]=0;
	}
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==Bit_SET)
	{
		bin_in[3]=1;
	}
	else
	{
		bin_in[3]=0;
	}
	zhuanghua(4);
}

u16 decide()
{
	u16 a;
	
		value_out=1;
		key_choice();
		key_ask();
		if(bin_in[0]==1)
		{
			a=13;
		}
		if(bin_in[1]==1)
		{
			a=14;
		}
		if(bin_in[2]==1)
		{
			a=15;
		}
		if(bin_in[3]==1)
		{
			a=16;
		}
		
		value_out *=2;
		if(bin_in[0]==1)
		{
			a=9;
		}
		if(bin_in[1]==1)
		{
			a=10;
		}
		if(bin_in[2]==1)
		{
			a=11;
		}
		if(bin_in[3]==1)
		{
			a=12;
		}
		
		value_out *=2;
		if(bin_in[0]==1)
		{
			a=5;
		}
		if(bin_in[1]==1)
		{
			a=6;
		}
		if(bin_in[2]==1)
		{
			a=7;
		}
		if(bin_in[3]==1)
		{
			a=8;
		}
		
		value_out *=2;
		if(bin_in[0]==1)
		{
			a=1;
		}
		if(bin_in[1]==1)
		{
			a=2;
		}
		if(bin_in[2]==1)
		{
			a=3;
		}
		if(bin_in[3]==1)
		{
			a=4;
		}
		
		if(value_in==8)
		{
			value_in=1;
		}
		return a;
	
}
 
