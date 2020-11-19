#include "weigh.h"
const unsigned char code Welcome[] = {"Welcome To Use!"};
const unsigned char title[] = {"By XZL & LLX"};
const unsigned char code PreWeight[] = {"Value:"};
const unsigned char digits[] = "0123456789";
const unsigned char code overWeight[] = {"超出量程"};
unsigned char WeightTab[9];                      // 存质量字符串
unsigned char code clearTable[] = {"         "}; // 清空

unsigned long var;
const unsigned long varPian = 400;
const float OneYuan = 2900.0;

unsigned char WeightString[8];
unsigned long temp; // 缓存质量
unsigned char k = 0;
unsigned long t; // 硬币个数

void init(void);
int loop(void);
char *int2str(unsigned long);
void calYingbi(unsigned long);
unsigned long abs(long);
void getOffset();

void main()
{
    init();
    while (1)
    {
        loop();
    }
}

int loop(void)
{
    temp = Hx711();
    display(2, 0, clearTable);
    calYingbi(temp);
    display(2, 0, int2str(t));

    return 0;
}

void init(void)
{
    delay(10);
    dis_init();
    display(0, 0, Welcome);
    display(1, 0, PreWeight);
    display(3, 0, title);
    getOffset();
}

/** 调用 times 次 nop 函数*/
void Nop(unsigned char times)
{
    int i = 0;
    for (i = 0; i < times; i++)
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
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < 100; j++)
            ;
    }
}

char *int2str(unsigned long values)
{
    char *crtn = WeightString;
    crtn += 7;
    *crtn = '\0';
    do
    {
        *--crtn = digits[values % 10];
    } while (values /= 10);
    return crtn;
}

void calYingbi(unsigned long temp)
{
    if (abs(temp - var) < varPian)
    {
        t = 0;
        return;
    }
    else
    {
        t = abs(temp - var) / OneYuan + 0.5;
        return;
    }
}

unsigned long abs(long i)
{
    if (i <= 0)
        return -i;
    return i;
}

void getOffset()
{
    unsigned char i = 0;
    unsigned long OffsetSum = 0;
    for (i = 0; i < 5; i++)
    {
        OffsetSum += Hx711();
    }
    var = OffsetSum / 5;
    return;
}