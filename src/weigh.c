#include "weigh.h"

const unsigned char title[] = {"硬币称重"};
const unsigned char overWeight[] = {"超出量程"};
const unsigned char clearTab[] = {"          "}; // 清屏某一行
unsigned char WeightTab[6];                      // 存质量字符串

float perWeight;   // 单个硬币质量
float totalWeight; // 总质量

void init(void);

void main()
{
    init();
    getOffset(10); // 初始化质量
    while (!loop());
}

int loop(void)
{
    WDT_FeedDog();
    unsigned float temp = getWeight();
    if (temp >= 1000)
    {
        display(0, 0, overWeight);
    }
    else if (temp == 0)
    {
        WeightTab[0] = '0';
    }
    else
    {
        weight_init();
        unsigned char k = 0;
        while (temp != 0)
        {
            WeightTable[k++] = 0x30 + temp % 10; //提取十进制最后一位转换为字符
            temp /= 10;
        }
    }
    write_cmd(0x93);
    while(k > 0){
        write_data(WeightTab[k--]);
    }
}

void init(void)
{
    time_init();
    dis_init();
    display(0, 0, title)
}

/** 调用 times 次 nop 函数*/
void Nop(unsigned char times)
{
    for (int i = 0; i < times; i++)
    {
        _nop_();
    }
    return;
}

/********************************************************************
函数名称: void delay(unsigned int x)	
功能简介: 晶振为11.0592MHZ时定时xms
入口参数: unsigned int x
返回值  ：无
*********************************************************************/
void delay(unsigned int x)
{
    unsigned int i, j = 110;
    for (i = 0; i < x; i++, j = 110)
    {
        while (j--);
    }
}