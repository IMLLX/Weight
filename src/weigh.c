#include "weigh.h"

const unsigned char code title[] = {"Ӳ�ҳ���"};
const unsigned char code overWeight[] = {"��������"};
unsigned char WeightTab[6]; // �������ַ���
unsigned char code clearTable[] = {"          "};			 // ���

unsigned char WeightString[8];
float perWeight;    // ����Ӳ������
float totalWeight;  // ������
unsigned long temp; // ��������
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
    getOffset(10); // ��ʼ������
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
            WeightTab[k++] = 0x30 + temp % 10; //��ȡʮ�������һλת��Ϊ�ַ�
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

/** ���� times �� nop ����*/
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
��������: void delay(unsigned int x)	
���ܼ��: ����Ϊ11.0592MHZʱ��ʱxms
��ڲ���: unsigned int x
����ֵ  ����
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