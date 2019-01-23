#include "keypad.h"
#include "stm32f10x.h"
#include "delay.h"
#include "oled.h"
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
 
/*���ļ��Ǿ��󰴼������ļ���ʹ�÷����ǣ�ֱ�ӵ�KEYPAD_Scan�����õ�һ������ֵ*/
 
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
 
//��������KEYPad_Init1
//��������
//���ܣ��м���ʼ��
//����ֵ;��
void KEYPad_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//����ʱ��,ʹ��GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//�������� B0-B3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//�������� B4-B7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
//��������KEYPad_Init2
//��������
//���ܣ��м���ʼ��
//����ֵ����
void KEYPad_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//����ʱ��,ʹ��GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//�������� B0-B3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//�������� B4-B7
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
//��������ɨ�躯��
//��ڲ�������
//����ֵ����ֵ
//���ܣ����󰴼�ɨ�裬����һ����ֵ
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
		delay_ms(8);//����10ms
		if(readvalue != 0x000f)
		{
			readvalue = GPIO_ReadInputData(GPIOA);//�ٴζ�ȡ״̬
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
			readvalue = GPIO_ReadInputData(GPIOA);//�ٴζ�ȡ״̬
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
			
			while(readvalue != 0x00f0)//��ⰴ���ɿ�
			{
				readvalue = GPIO_ReadInputData(GPIOA);//�ٴζ�ȡ״̬
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
