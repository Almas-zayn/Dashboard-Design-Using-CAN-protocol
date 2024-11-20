#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "delay.h"
#include "Accmtr_defines.h"

void Accmtr_MODE(s8 modeval)
{
  i2c_start();  
  i2c_write(Accmtr<<1);
        i2c_write((MODEREG));    //clearing modereg
        i2c_write(modeval);    //1 for activemode & setting sample bit,0,4
        i2c_stop();
        delay_ms(10);
}

void Accmtr_SAMPLE(s8 sample)
{
        i2c_start();    
        i2c_write(Accmtr<<1);
        i2c_write((SRREG)&0xFF);    //clearing modereg
        i2c_write(sample);//120 samples per second
        i2c_stop();
        delay_ms(10);
}       
void Init_Accmtr(void)
{
        Accmtr_MODE(STANDBY_MODE);
        Accmtr_SAMPLE(_32SPS);
        Accmtr_MODE(ACTIVE_MODE);
}                

s8 Accmtr_Read(u8 axis_addr)
{
       s8 dat;
        i2c_start();    
        i2c_write(Accmtr<<1);
        i2c_write((axis_addr));    //Z OR Y OR Z
        i2c_restart();  
        i2c_write(Accmtr<<1|1);
        dat=i2c_nack(); 
        i2c_stop();
        return dat;
}

void Accmtr_XYZREAD(s32 *ArrPtr)
{
        int i;
        for(i=0;i<3;i++)
        {
                ArrPtr[i]=Accmtr_Read(XAREG+i);
                if(((ArrPtr[i]>>6)&1))//checking if alert bit is set,if set reading again
                {
                        i--;
                        delay_ms(2);
                        continue;
                }
                 if(((ArrPtr[i])>>5)&1)                                                                                               
                     ArrPtr[i]=-(ArrPtr[i]&0x1f);                      
                 else                         
                     ArrPtr[i]=(ArrPtr[i]&0x1f);                      
        }
}

void Accmtr_Gravity(f32 *arr)
{
        int i;
        for(i=0;i<3;i++)
        {
                arr[i]=arr[i]*0.047;//for 1 unit 0.047g
        }
}

void Accmtr_Degree(f32 *arr)
{
        int i;
        for(i=0;i<3;i++)
        {
                if(i==2)
                {
                   arr[i]=90-(arr[i]*(2.69));// 0 is 90.0 degree for z it is opposit
                }
                else
                   arr[i]=arr[i]*(2.69);//for 1 unit 2.69degree
        }
}

s32 AIRBAG(s32 *arr)
{
     if(arr[2]<3) 
     {
       if(((arr[0]>=0)&&(arr[0]<=24))||(arr[0]<=-12))
          return 1;
       else if(((arr[1]>=0)&&(arr[1]<=24))||(arr[1]<=-12))
          return 1;
     }
     return 0;
}

