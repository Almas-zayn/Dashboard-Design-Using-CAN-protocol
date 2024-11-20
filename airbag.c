#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "accelerometer.h"
#include "Accmtr_defines.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
#define AIRBAG_LED_ 0

int axis[3];
extern int i;

void AirBag()
{
	 for(i=0;i<3;i++)
	 {
	     axis[i]=Accmtr_Read(XAREG+i);
	     if((axis[i]>>5&1)==1)
	   	  	axis[i]=-(axis[i]&0x1f);
	     else
	   		  axis[i]=axis[i]&0x1f;
	 }	 
	 if(AIRBAG(axis))
	 {
        CmdLCD(GOTO_LINE4_POS0+9);
        StrLCD("OPEN ");
	      IOCLR0=1<<AIRBAG_LED_;
	 }
	 else
	 {
		    CmdLCD(GOTO_LINE4_POS0+9);
        StrLCD("CLOSE");
	   	  IOSET0=1<<AIRBAG_LED_;
	 }
	 delay_ms(50);
}
