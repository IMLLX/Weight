#include <reg52.h>
#include <intrins.h>
#include "Ad.h"
#include "display.h"
#include "key.h"
#include "init.h"

// extern unsigned long Hx711(void);

// extern float AD_Weight(unsigned long ADvalue);
extern void AD_Offset();
extern unsigned long Offset;
extern float Weight;
extern float WeightTemp; 
extern unsigned char clearTab[];


extern void delay(int );
extern void Nop(unsigned char times);

