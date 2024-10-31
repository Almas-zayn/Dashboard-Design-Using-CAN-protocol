#include<LPC21xx.h>
#include"adc.h"
#include"can.h"
#define MAX 2.441
#define Min 0.290

float recv_fuel_per;
int fuel;
void CAL(void);

CANF fuel_tx_Frame;

int main()
 {
    Init_ADC();
    Init_CAN1();
     while(1)
     {
        recv_fuel_per=Read_ADC(1);				
				fuel=(((recv_fuel_per-Min)/(MAX-Min))*100);
				CAL();				    
        fuel_tx_Frame.ID=4;
        fuel_tx_Frame.vbf.RTR=0;
        fuel_tx_Frame.vbf.DLC=4;
        fuel_tx_Frame.Data1=fuel;
        CAN1_Tx(fuel_tx_Frame);
      }

}
 
void CAL(void)
{
			if((fuel <= 100) && (fuel > 75))
          fuel_tx_Frame.Data2=4;				
      else if(fuel > 50 && fuel <= 75)
          fuel_tx_Frame.Data2=3;           
      else if(fuel <= 50 && fuel > 25)
          fuel_tx_Frame.Data2=2;     
      else 
          fuel_tx_Frame.Data2=1;
}
	
	