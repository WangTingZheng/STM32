#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "stm32f10x.h"
#include "key.h"
#include "keypad.h"
#include "delay.h"
 
 int main(void)
 {	
	//all_init();
	key_scan();
}

