#include "weigh.h"
#include "Ad.h"
#define StandardValue 1600000 // 质量基准值

sbit DOUT = P1^3;       // 串行输入数据端
sbit PD_CLK = P1^4;     // 时钟信号端
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
    unsigned long AD_Value = 0;
    unsigned char i = 0;
    PD_CLK = 0;
    while (DOUT);
    for (i = 0; i < 24; i++)
    {
        PD_CLK = 1;
        Nop(3);
        AD_Value = AD_Value << 1;
        PD_CLK = 0;
        if (DOUT)
        {
            AD_Value++;
        }
    }
    PD_CLK = 1;
    AD_Value = AD_Value ^ 0x800000; // 输出补码
    PD_CLK = 0;
    Nop(3);
    return AD_Value;
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
    while (i > 0)
    {
        AD_Sum = AD_Sum + Hx711();
        i--;
    }

    Offset = (unsigned long)(AD_Sum / 5);
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
    return (float)Dvalue / StandardValue * 4000;
}
