#include<LPC21xx.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "adc.h"
#include "delay.h"
#include "defines.h"
#include "indicator_interupt.h"
#include "can.h"
#include "types.h"

  void read_Accelerometer(void);
  void fuel_Per(void);
  void indicator_Signal(void);
  void starting_msg(void);
	
CANF fuel_rx_Frame;
u32 rflag=0,lflag=0;
u32 cur_fuel_per=0,i=0,fuel;

int main()
{
    InitLCD();
    Init_Intrpt();
    Init_CAN1();
    starting_msg();
    while(1)
		{
        read_Accelerometer();
        fuel_Per();
        indicator_Signal();
    }
}

void read_Accelerometer()
{

}

void fuel_Per()
 {
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("Fuel-");
    CAN1_Rx(&fuel_rx_Frame);
	  if(fuel_rx_Frame.ID == 4){
      cur_fuel_per=fuel_rx_Frame.Data1; //get data from fuel indicator
      fuel=fuel_rx_Frame.Data2;
		}
		U32LCD(cur_fuel_per);
    for(i=1;i<=4;i++)
    {
        if(i<=fuel)                     
           CmdLCD(DSP_ON_CUR_ON);
		    else
           CmdLCD(DSP_ON_CUR_OFF);
        CmdLCD(GOTO_LINE2_POS0+i);
    }
 }

void indicator_Signal()
{
    CmdLCD(GOTO_LINE2_POS0);
    if(lflag==1)
    {
             StrLCD("Left-ON");
             delay_ms(100);
    }
    if(rflag==1)
    {
             StrLCD("Right-ON");
             delay_ms(100);
    }

}

void starting_msg(void)
{
	CmdLCD(GOTO_LINE1_POS0);
  StrLCD("PROJ- V23HE11A10");
  CmdLCD(GOTO_LINE2_POS0);
  StrLCD("DASHBOARD DESIGN");
  delay_s(2);
}
				
				
				