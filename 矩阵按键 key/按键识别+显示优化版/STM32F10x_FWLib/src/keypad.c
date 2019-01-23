#include "keypad.h"
#include "stm32f10x.h"
#include "delay.h"
#include "oled.h"
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
 
/*本文件是矩阵按键功能文件，使用方法是：直接调KEYPAD_Scan函数得到一个返回值*/
 
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
 
//函数名：KEYPad_Init1
//参数：无
//功能：行检测初始化
//返回值;无
void KEYPad_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启时钟,使能GPIOB时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入 B0-B3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入 B4-B7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
//函数名：KEYPad_Init2
//参数：无
//功能：列检测初始化
//返回值：无
void KEYPad_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启时钟,使能GPIOB时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入 B0-B3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入 B4-B7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
void KEYPAD_print(u16 a)
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
//函数名：扫描函数
//入口参数：无
//返回值：键值
//功能：矩阵按键扫描，返回一个键值
u16 KEYPAD_Scan()
{
	static u16 keyvalue = 0;
	u32 readvalue = 0;
	KEYPad_Init1();
	readvalue = GPIO_ReadInputData(GPIOA);
	readvalue &= 0x00ff;
	//return readvalue;
	if(readvalue != 0x000f)
	{
		delay_ms(8);//消抖10ms
		if(readvalue != 0x000f)
		{
			readvalue = GPIO_ReadInputData(GPIOA);//再次读取状态
			readvalue &= 0x00ff;
			//return readvalue;
			switch(readvalue)
			{
				case (0x001f):keyvalue = 0;break;
				case (0x002f):keyvalue = 1;break;
				case (0x004f):keyvalue = 2;break;
				case (0x008f):keyvalue = 3;break;
			}
			//return readvalue;
			KEYPad_Init2();
			delay_ms(5);
			readvalue = GPIO_ReadInputData(GPIOA);//再次读取状态
			readvalue |= 0x00f0;
			readvalue &= 0x00ff;
			//return readvalue;
			switch(readvalue)
			{
				case (0x00f1):keyvalue += 0;break;
				case (0x00f2):keyvalue += 4;break;
				case (0x00f4):keyvalue += 8;break;
				case (0x00f8):keyvalue += 12;break;
			}
			
			while(readvalue != 0x00f0)//检测按键松开
			{
				readvalue = GPIO_ReadInputData(GPIOA);//再次读取状态
				readvalue |= 0x00f0;
				readvalue &= 0x00ff;
			}
			//return readvalue;
		}
	}
	return keyvalue;
}
void test(void)
{
		KEYPad_Init1();
		GPIO_Write(GPIOA,0x00f0);
		KEYPAD_print(KEYPAD_Scan());
}
