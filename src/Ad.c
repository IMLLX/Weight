#include "weigh.h"
#include "Ad.h"
#define gapValue 4000

sbit DOUT = P1 ^ 2;       // �����������ݶ�
sbit PD_CLK = P1 ^ 3;     // ʱ���źŶ�
unsigned long Offset = 0; // ���ƫ��
float Weight = 0;         // ����
float WeightTemp = 0.0;   // �����м����

/********************************************************************
��������: unsigned long AD_Hx711(void)
���ܼ��: AD�ɼ�
��ڲ���: ��
����ֵ  ��ģ���ѹ����ADת�����������
*********************************************************************/
unsigned long Hx711(void)
{
    unsigned long Count;
    unsigned char i;
    PD_CLK = 0;                 // ʹ�� AD �� PD_PD_CLK �õͣ�
    Count = 0;
    while (DOUT)
        ;                       //AD ת��δ������ȴ�������ʼ��ȡ
    for (i = 0; i < 24; i++)
    {
        PD_CLK = 1;             //PD_PD_CLK �øߣ��������壩
        Count = Count << 1;     // �½�����ʱ���� Count ����һλ���Ҳಹ��
        PD_CLK = 0;             //PD_PD_CLK �õ�
        if (DOUT)
            Count++;
    }
    PD_CLK = 1;
    Count = Count ^ 0x800000; // �� 25 �������½�����ʱ��ת������
    PD_CLK = 0;
    return (Count);
}

/********************************************************************
��������: void AD_Offset(unsigned char i)		
���ܼ��: AD�ɼ����ƫ��ƽ��ֵ��Ҳ�ɵ�ȥƤʹ��
��ڲ���: �ɼ�����
����ֵ  ����
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
��������: unsigned float getWeight(void)
���ܼ��: ADֵת��Ϊ��gΪ��λ������
��ڲ���: UINT_32 ADvalue
����ֵ  ��ת������gΪ���ٵ�����ֵ
*********************************************************************/
float getWeight(void)
{
    unsigned long Dvalue = Hx711() - Offset; // ֵ��С��0
    if (Dvalue < 0)
    {
        Dvalue = 0;
    }
    return (float)Dvalue / gapValue;
}
