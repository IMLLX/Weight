#include "weigh.h"
#include "Ad.h"
#define StandardValue 1600000 // ������׼ֵ

sbit DOUT = P1^3;       // �����������ݶ�
sbit PD_CLK = P1^4;     // ʱ���źŶ�
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
    AD_Value = AD_Value ^ 0x800000; // �������
    PD_CLK = 0;
    Nop(3);
    return AD_Value;
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
    while (i > 0)
    {
        AD_Sum = AD_Sum + Hx711();
        i--;
    }

    Offset = (unsigned long)(AD_Sum / 5);
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
    return (float)Dvalue / StandardValue * 4000;
}
