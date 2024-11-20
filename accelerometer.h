#ifndef __Accmtr_H__
#define __Accmtr_H__
#include "types.h"
void Init_Accmtr(void);
void Accmtr_MODE(s8);//mode_val
s32 AIRBAG(s32 *);
s32 Accmtr_Read(u8);//axis_reg addr
void Accmtr_XYZREAD(s32 *);//array name 
void Accmtr_SAMPLE(void);
void Accmtr_Gravity(f32 *);
void Accmtr_Degree(f32 *);
void AirBag(void);
#endif
