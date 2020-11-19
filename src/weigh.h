#include <reg52.h>
#include <intrins.h>

#ifndef _WEIGHT_
#define _WEIGHT_
#include "Ad.h"
#include "display.h"
#include "key.h"
#include "init.h"


extern unsigned long Offset;
extern float Weight;
extern float WeightTemp; 


extern void delay(unsigned int );
extern void Nop(unsigned char times);

#endif