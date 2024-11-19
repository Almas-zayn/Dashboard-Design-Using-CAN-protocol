#include<LPC21xx.h>
#include"adc.h"
#include "delay.h"
#include"can.h"
#define Maximum 2.46
#define Minimum 0.25

float recv_fuel_per;
int fuel;

CANF fuel_tx_Frame;

int main()
{
    Init_ADC();
    Init_CAN1();
        fuel_tx_Frame.ID=4;
        fuel_tx_Frame.vbf.RTR=0;
        fuel_tx_Frame.vbf.DLC=4;
     while(1)
     {
       recv_fuel_per=Read_ADC(0);
       if(recv_fuel_per<Minimum)
           recv_fuel_per=Minimum;

       else if(recv_fuel_per>Maximum)
           recv_fuel_per=Maximum;

       fuel=(((recv_fuel_per-Minimum)/(Maximum-Minimum))*100);

       fuel_tx_Frame.Data1=fuel;
       CAN1_Tx(fuel_tx_Frame);
       delay_ms(100);
     }
}	
	
