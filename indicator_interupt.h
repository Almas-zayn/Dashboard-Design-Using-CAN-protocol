#ifndef __INDICATOR_INTERUPT_H__
#define __INDICATOR_INTERUPT_H__
#include<LPC21xx.h>
#include "can.h"
#define ch1 14
#define ch2 15

extern u32 rflag,lflag;
void Init_Intrpt(void);
void right_Indicator(void) __irq;
void left_Indicator(void) __irq;

#endif

