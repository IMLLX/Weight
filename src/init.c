#include "weigh.h"
#include "init.h"

void time_init(void)
{
    TMOD = 0X11; // ���ö�ʱ��0,1Ϊ����ģʽ1
    TH0 = 238;
    TL0 = 0; // װ��ֵ,��ʱʱ��Ϊ5ms
    EA = 1;  // �������ж�����
    ET0 = 1; // ������ʱ��0�ж�
    ET1 = 1; // ������ʱ��1�ж�
    TR0 = 1; // ������ʱ��0
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