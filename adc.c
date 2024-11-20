#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "adc_defines.h"

void Init_ADC(void)
{
	//def already ain0,ain1,ain2,ain3
	//confgd by start up code
	//cfg ADCR sfr
	ADCR=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_START_BIT);	
}

f32 Read_ADC(u32 chNo)
{
	u32 adcDVal;
	f32 eAR;
	//masking channel No
	ADCR&=0xFFFFFF00;
	//update channel No & start adc converstion
	ADCR|=(1<<ADC_START_BIT)|(1<<chNo);
	//wait for > 2.44us
	delay_us(3);
	//check status of conversion complete	while(READBIT(ADDR,DONE_BIT)==0);
	CLRBIT(ADCR,ADC_START_BIT);
	adcDVal=((ADDR>>RESULT_START_BIT)&1023);
	eAR=(adcDVal*(3.3/1023));
	return eAR;
}
