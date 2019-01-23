#ifndef __KEYPAD_H
#define __KEYPAD_H
#include "sys.h"
#include "stdlib.h"	
#include "stm32f10x.h"
u16 KEYPAD_Scan(void);
void KEYPAD_print(u16 a);
void test(void);
#endif
