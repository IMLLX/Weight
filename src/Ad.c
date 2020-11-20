#include "weigh.h"
#include "Ad.h"
#define gapValue 4000

sbit DOUT = P1 ^ 2;
sbit PD_CLK = P1 ^ 3;
unsigned long Offset = 0;
float Weight = 0;
float WeightTemp = 0.0;

unsigned long Hx711(void)
{
    unsigned long Count;
    unsigned char i;
    PD_CLK = 0;
    Count = 0;
    while (DOUT)
        ;
    for (i = 0; i < 24; i++)
    {
        PD_CLK = 1;
        Count = Count << 1;
        PD_CLK = 0;
        if (DOUT)
            Count++;
    }
    PD_CLK = 1;
    Count = Count ^ 0x800000;
    PD_CLK = 0;
    return (Count);
}
