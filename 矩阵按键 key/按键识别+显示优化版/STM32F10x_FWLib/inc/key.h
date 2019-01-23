#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#include "stdlib.h"	
#include "stm32f10x.h"
void all_init(void);
void key_print(u16 a);
void key_scan(void);
u16 decide(void);
#endif
