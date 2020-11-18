#include "weigh.h"
#include "init.h"

void time_init(void)
{
    TMOD = 0X11; // 设置定时器0,1为工作模式1
    TH0 = 238;
    TL0 = 0; // 装初值,定时时间为5ms
    EA = 1;  // 开启总中断允许
    ET0 = 1; // 开启定时器0中断
    ET1 = 1; // 开启定时器1中断
    TR0 = 1; // 启动定时器0
}

// void weight_init(unsigned char *weight)
// {
//     while (*weight != '\0')
//     {
//         *weight++ = clearTab;
//     }
// }

void init_WeiTag(unsigned char *str1, unsigned char *str2)
{
    unsigned char i;
    for (i = 0; i < 5; i++)
    {
        *str1++ = *str2;
    }
}