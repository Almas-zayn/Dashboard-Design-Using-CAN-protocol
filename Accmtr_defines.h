#ifndef __Accmtr_DEFINES_H__
#define __Accmtr_DEFINES_H__
//MMA660 slave
#define Accmtr 	0x4c

//register addresses
#define MODEREG 0x07
#define SRREG  0x08
#define XAREG 0x00
#define YAREG 0x01
#define ZAREG 0x02
#define TILTREG 0x03

//modes	
#define STANDBY_MODE 	0x00
#define ACTIVE_MODE  	0x11 //0,4 bits, 0for mode,4 for samplerate

//samples per second
#define _120SPS	     	0x00
#define _64SPS       	0x01
#define _32SPS       	0x02
#define _16SPS       	0x03
#define _8SPS        	0x04
#define _4SPS        	0x05
#define _2SPS        	0x06
#define _1SPS        	0x07
#endif
