#include "weigh.h"
sbit Key1 = P2 ^ 0; //һԪ
sbit Key2 = P2 ^ 1; //��ë
sbit Key3 = P2 ^ 2; //һë
sbit Key4 = P2 ^ 3; //��λ

unsigned char ReadKey(void)
{
    P3 = 0xff;
    if (Key1 == 0)
    {
        delay(5);
        if (Key1 == 0)
            return 1;
    }
    else if (Key2 == 0)
    {
        delay(5);
        if (Key2 == 0)
            return 2;
    }
    else if (Key3 == 0)
    {
        delay(5);
        if (Key3 == 0)
            return 3;
    }
    else if (Key4 == 0)
    {
        delay(5);
        if (Key4 == 0)
            return 4;
    }
    return 0;
}