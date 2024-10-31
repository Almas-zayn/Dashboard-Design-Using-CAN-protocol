#include<LPC21xx.h>
#include"can.h"
#include"delay.h"
#include"can_defines.h"
#define LED 8
#define LEFT_INDI 1
#define RIGHT_INDI 2
#define ON 1
#define OFF 2

CANF Indicator_rx;
int i;

int main()
{
	Init_CAN1();
	IODIR0|=255<<LED;
	   Indicator_rx.Data1=0;
		 Indicator_rx.ID=0;
	
	while(1)
	{
		if((C1GSR & RBS_BIT_READ) == 0);
		else
		   CAN1_Rx(&Indicator_rx);
		
		if(Indicator_rx.ID == LEFT_INDI) // LEFT INDICATOR
		{
			if(Indicator_rx.Data1 == ON)
			{
			  for(i=0;i<LED;i++,delay_ms(100))
				     IOSET0|=(1<<i)<<LED;
			}
			if(Indicator_rx.Data1 == OFF)
			       IOCLR0|=255<<LED;
		}
		
		if(Indicator_rx.ID == RIGHT_INDI) // RIGHT INDICATOR
		{
			if(Indicator_rx.Data1 == ON)
			{
			  for(i=LED;i>=0;i--,delay_ms(100))
				     IOSET0|=(1<<i)<<LED;
		  }
		  if(Indicator_rx.Data1 == OFF)
			       IOCLR0|=255<<LED;
		}
	}
}