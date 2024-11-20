#include "indicator_interupt.h"
#include "lcd.h"
#include "lcd_defines.h"

CANF indicator_tx_Frame;

void right_Indicator(void) __irq
{
   ++rflag;
   if(rflag == 1)
   {
         indicator_tx_Frame.ID=1;
         indicator_tx_Frame.vbf.RTR=0;
         indicator_tx_Frame.vbf.DLC=4;
         indicator_tx_Frame.Data1=rflag;
         CAN1_Tx(indicator_tx_Frame);
		     CmdLCD(GOTO_LINE3_POS0 + 15);
		     StrLCD(">>>");
   }
   if(rflag == 2)
   {
         indicator_tx_Frame.ID=1;
         indicator_tx_Frame.vbf.RTR=0;
         indicator_tx_Frame.vbf.DLC=4;
         indicator_tx_Frame.Data1=rflag;
         CAN1_Tx(indicator_tx_Frame);
		     CmdLCD(GOTO_LINE3_POS0 + 15);
		     StrLCD("   ");
         rflag=0;
   }
   EXTINT=1<<0;
   VICVectAddr=0;
}

void left_Indicator(void) __irq
{
   ++lflag;
   if(lflag == 1)
   {
         indicator_tx_Frame.ID=2;
         indicator_tx_Frame.vbf.RTR=0;
         indicator_tx_Frame.vbf.DLC=4;
         indicator_tx_Frame.Data1=lflag;
         CAN1_Tx(indicator_tx_Frame);
		     CmdLCD(GOTO_LINE3_POS0 + 1);
		     StrLCD("<<<");
   }
   if(lflag == 2)
   {
         indicator_tx_Frame.ID=2;
         indicator_tx_Frame.vbf.RTR=0;
         indicator_tx_Frame.vbf.DLC=4;
         indicator_tx_Frame.Data1=lflag;
         CAN1_Tx(indicator_tx_Frame);
		     CmdLCD(GOTO_LINE3_POS0 + 1);
		     StrLCD("   ");
         lflag=0;
   }
   EXTINT=1<<1;
   VICVectAddr=0;
}

void Init_Intrpt(void)
{
  PINSEL0|=0x20000000;
	PINSEL1|=0x15400001;
  VICIntEnable=(1<<ch1)|(1<<ch2);

  VICVectCntl0=(0x20)|ch1;
  VICVectAddr0=(unsigned long)right_Indicator;

  VICVectCntl1=0x20|ch2;
  VICVectAddr1=(unsigned long)left_Indicator;
  EXTMODE=(1<<0)|(1<<1);
}

