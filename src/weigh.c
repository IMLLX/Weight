#include "weigh.h"

const unsigned char code title[] = {"硬币称重"};
const unsigned char code overWeight[] = {"超出量程"};
unsigned char WeightTab[6]; // 存质量字符串
unsigned char code clearTable[] = {"          "};			 // 清空

unsigned char WeightString[8];
float perWeight;    // 单个硬币质量
float totalWeight;  // 总质量
unsigned long temp; // 缓存质量
unsigned char k = 0;
unsigned char t;


sbit wela = P2 ^ 6;
sbit dula = P2 ^ 7;

void init(void);
int loop(void);
void mitoa(int, char str[]);

void mitoa(int num, char str[])
{
    int sign;
    unsigned char i = 0, j = 0;
    unsigned char temp[10];
    sign = num;
    do
    {
        temp[i] = sign % 10 + '0';
        sign /= 10;
        i++;
    } while (sign > 0);
    while (i > 0)
    {
        str[j] = temp[i - 1];
        j++;
        i--;
    }
    str[j] = '\0';
}

void main()
{
    init();
    getOffset(10); // 初始化质量
    while (!loop())
        ;
}

int loop(void)
{
    temp = 0;
    temp = getWeight();
    // if (temp >= 1000)
    // {
    //     display(0, 0, overWeight);
    // }
    if (temp == 0)
    {
        WeightTab[0] = '0';
        k = 1;
    }
    else
    {
        init_WeiTag(WeightTab,clearTable);
        k = 0;
        while (temp != 0)
        {
            WeightTab[k++] = 0x30 + temp % 10; //提取十进制最后一位转换为字符
            temp /= 10;
        }
    }
    write_cmd(0x93);
    while (k > 0)
    {
        write_data(WeightTab[k--]);
    }
    return 0;
}

void init(void)
{
    dula = 1;
    P0 = 0xff;
    dula = 0;
    wela = 1;
    P0 = 0x00;
    wela = 0;
    delay(10);
    // time_init();
    dis_init();
    display(0, 0, "Hello World");
    display(2,0,title);
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