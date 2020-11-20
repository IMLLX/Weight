#include "weigh.h"
#include "queue.h"
unsigned long queue[3];
unsigned char curr = 0;

void push(unsigned long val)
{
    if (curr > 2)
        return;
    queue[++curr] = val;
    return;
}

void pull()
{
    if (curr == 0)
        return;
    queue[0] = queue[1];
    queue[1] = queue[2];
    queue[2] = 0;
    curr--;
    return;
}

unsigned long averQue()
{
    unsigned char i = 0;
    unsigned long sum = 0;
    for (i = 0; i < 3; i++)
    {
        sum += queue[i];
    }
    return sum / 3;
}

void initQue()
{
    unsigned char i;
    clearQue();
    for (i = 0; i < 3; i++)
    {
        push(Hx711());
    }
    curr = 2;
    return;
}

void clearQue()
{
    queue[0] = 0;
    queue[1] = 0;
    queue[2] = 0;
    curr = 0;
    return;
}