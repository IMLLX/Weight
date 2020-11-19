#include "weigh.h"
#include "Ad.h"
#define gapValue 4000

sbit DOUT = P1 ^ 2;       // 串行输入数据端
sbit PD_CLK = P1 ^ 3;     // 时钟信号端
unsigned long Offset = 0; // 零点偏移
float Weight = 0;         // 质量
float WeightTemp = 0.0;   // 质量中间变量

/********************************************************************
函数名称: unsigned long AD_Hx711(void)
功能简介: AD采集
入口参数: 无
返回值  ：模拟电压经过AD转化后的数字量
*********************************************************************/
unsigned long Hx711(void)
{
    unsigned long Count;
    unsigned char i;
    PD_CLK = 0;                 // 使能 AD （ PD_PD_CLK 置低）
    Count = 0;
    while (DOUT)
        ;                       //AD 转换未结束则等待，否则开始读取
    for (i = 0; i < 24; i++)
    {
        PD_CLK = 1;             //PD_PD_CLK 置高（发送脉冲）
        Count = Count << 1;     // 下降沿来时变量 Count 左移一位，右侧补零
        PD_CLK = 0;             //PD_PD_CLK 置低
        if (DOUT)
            Count++;
    }
    PD_CLK = 1;
    Count = Count ^ 0x800000; // 第 25 个脉冲下降沿来时，转换数据
    PD_CLK = 0;
    return (Count);
}

/********************************************************************
函数名称: void AD_Offset(unsigned char i)		
功能简介: AD采集零点偏移平均值，也可当去皮使用
入口参数: 采集次数
返回值  ：无
*********************************************************************/
void getOffset(unsigned char i)
{
    unsigned long AD_Sum = 0;
    unsigned char t = i;
    while (i > 0)
    {
        AD_Sum = AD_Sum + Hx711();
        i--;
    }

    Offset = (unsigned long)(AD_Sum / t);
}

/********************************************************************
函数名称: unsigned float getWeight(void)
功能简介: AD值转换为以g为单位的质量
入口参数: UINT_32 ADvalue
返回值  ：转化后以g为量纲的质量值
*********************************************************************/
float getWeight(void)
{
    unsigned long Dvalue = Hx711() - Offset; // 值会小于0
    if (Dvalue < 0)
    {
        Dvalue = 0;
    }
    return (float)Dvalue / gapValue;
}
