#include "weigh.h"

#define OneYuan 2725.0
#define WuJiao 1700.0
#define YiJiao 1440.0
#define varPian 1000
#define noise 100

const unsigned char code Welcome[] = {"Welcome To Use!"};
// const unsigned char title[] = {"By XZL & LLX"};
const unsigned char code PreWeight[] = {"Coins Count:"};
const unsigned char code YuanStr[] = {"     YiYuan"};
const unsigned char code YuanStr2[] = {"     Yuan"};
const unsigned char code WuJiaoStr[] = {"     WuJiao"};
const unsigned char code JiaoStr[] = {"     YiJiao"};
const unsigned char code JiaoStr2[] = {"     Jiao"};
const unsigned char code ValueStr[] = {"Value:"};
const unsigned char code ClearNumber[] = {"     "};

const unsigned char digits[] = "0123456789";
const unsigned char code ChoosePage[] = {"Press A Button:"};

// const unsigned long varPian = 1000; // 有硬币最低质量
// const unsigned long noise = 100;    // 允许噪声范围
// const float OneYuan = 2725.0;
// const float WuJiao = 1700.0;
// const float YiJiao = 1440.0;

unsigned char WeightString[8]; // 质量字符串
unsigned char ValueString[8];  // 质量字符串
unsigned long temp;            // 缓存平均质量
unsigned short t;              // 硬币个数
unsigned short value;          // 硬币面值
unsigned char flag;            // 上次按键
unsigned long var;             // 基准值

float currCoinValue;  // 当前硬币面值
float currCoinWeight; // 当前模式的硬币质量

void init(void);
void loop(void);
void calYingbi(unsigned long);
void calValue(void);
void getOffset(void);

char *int2str(unsigned long);
char *float2str(float);
unsigned long averHx(int);
unsigned long abs(long);

void main()
{
    init();
    P2 = 0xff;
    while (1)
    {
        unsigned currKey = ReadKey();
        if (currKey == KEY1 || (flag == KEY1 && currKey == 0))
        {
            if (flag != KEY1)
            {
                dis_init();
                display(1, 0, YuanStr);
                currCoinWeight = OneYuan;
                currCoinValue = 1.0;
                display(3, 0, YuanStr2);
            }
            flag = KEY1;
            loop();
        }
        else if (currKey == KEY2 || (flag == KEY2 && currKey == 0))
        {
            if (flag != KEY2)
            {
                dis_init();
                display(1, 0, WuJiaoStr);
                currCoinWeight = WuJiao;
                currCoinValue = 0.5;
                display(3, 0, JiaoStr2);
            }
            flag = KEY2;
            loop();
        }
        else if (currKey == KEY3 || (flag == KEY3 && currKey == 0))
        {
            if (flag != KEY3)
            {
                dis_init();
                display(1, 0, JiaoStr);
                currCoinWeight = YiJiao;
                currCoinValue = 0.1;
                display(3, 0, JiaoStr2);
            }
            flag = KEY3;
            loop();
        }
        else if (currKey == KEY4 || (flag == KEY4 && currKey == 0))
        {
            if (flag != KEY4)
            {
                dis_init();
                getOffset();
            }
            flag = KEY4;
            loop();
        }
    }
}

void loop(void)
{
    unsigned short last = t; // 上次硬币个数

    if (flag != KEY4)
    {
        display(0, 0, PreWeight);
        display(2, 0, ValueStr);
        pull();
        push(temp = Hx711());
        if (abs(temp - averQue()) > noise)
        {
            clearQue();
            initQue();
            return;
        }
        calYingbi(temp);
        calValue();
        if (last != t)
        {
            display(1, 0, ClearNumber);
            display(1, 0, int2str(t));
            display(3, 0, ClearNumber);
            display(3, 0, int2str(value));
        }
        return;
    }
    else
    {
        display(0, 0, "Current:");
        pull();
        push(Hx711());
        clearTable(1);
        display(1, 0, int2str(abs(averQue() - var)));
    }
}

void init(void)
{
    delay(10);
    dis_init();
    display(0, 0, Welcome);
    display(1, 0, ChoosePage);
    initQue();
    getOffset();
}

void Nop(unsigned char times)
{
    int i = 0;
    for (i = 0; i < times; i++)
    {
        _nop_();
    }
    return;
}

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
        t = abs(temp - var) / currCoinWeight + 0.5;
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
    var = averHx(3);
    if (abs(var - averQue()) > noise)
    {
        initQue();
        getOffset();
    }
    return;
}

unsigned long averHx(int times)
{
    unsigned char i = 0;
    unsigned long average = 0;
    for (i = 0; i < times; i++)
    {
        average += Hx711();
    }
    average = average / times;
    return average;
}

void calValue(void)
{
    if (currCoinValue != 1.0)
    {
        value = (t * currCoinValue) / 0.1;
    }
    else
        value = t;
    return;
}