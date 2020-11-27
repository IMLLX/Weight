#include "weigh.h"
#define LCD_BUS P0 // 12864Һ���ӿ�����

sbit LCD_RS = P3 ^ 5;  // �͵�ƽΪдָ��ߵ�ƽΪд���ݶ�
sbit LCD_RW = P3 ^ 6;  // �͵�ƽΪд���ߵ�ƽΪ��
sbit LCD_EN = P3 ^ 4;  // ʹ�ܶ�
sbit LCD_PSB = P3 ^ 7; // ��������
sbit busy = P0 ^ 7;    // æ�˿�

/********************************************************************
��������: void Check_Busy()		
���ܼ��: �����12864Һ���ڲ�����״̬
��ڲ���: ��
����ֵ  ����
*********************************************************************/
void await_lcd()
{
    LCD_BUS = 0xff; // ��LCD_BUS����Ϊ�����
    LCD_RS = 0;
    LCD_RW = 1; // ��
    LCD_EN = 1;
    delay(5);
    while ((LCD_BUS & 0x80) == 0x80)
        ; // LCD_BUS���λΪSTA7����ֵ��0���������1��ֹ
    // while (!LCD_BUS);
    // while (busy);
    LCD_EN = 0;
}

/********************************************************************
��������: void write_cmd(unsigned char cmd)	
���ܼ��: 12864Һ��дָ��
��ڲ���: UINT_8 cmd
����ֵ  ����
*********************************************************************/
void write_cmd(unsigned char cmd)
{
    await_lcd();
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    LCD_BUS = cmd;
    delay(5);
    LCD_EN = 1; //��ʹ�ܶ�LCD_EN������ʱ��ָ��cmdд��
    delay(5);
    LCD_EN = 0;
}

/********************************************************************
��������: void write_data(unsigned char dat)
���ܼ��: 12864Һ��д����
��ڲ���: UINT_8 data
����ֵ  ����
*********************************************************************/
void write_data(unsigned char dat)
{
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    LCD_BUS = dat;
    Nop(3);
    LCD_EN = 1;
    Nop(3);
    LCD_EN = 0;
}

/********************************************************************
��������: dis_init()
���ܼ��: 12864Һ����ʼ��
��ڲ���: ��
����ֵ  ����
*********************************************************************/
void dis_init()
{
    Nop(3);
    LCD_PSB = 1;     // ����
    write_cmd(0x30); // 8Ϊ���У�ָ��Ϊ����ָ��
    write_cmd(0x0c); // ��ʾ��
    write_cmd(0x01); // ����
    write_cmd(0x06);
}

/********************************************************************
��������: void display(unsigned char x, unsigned char y, unsigned char *string)	
���ܼ��: Һ��DDRAM��ַѡ����ʾ,xѡ���У�yѡ���У�stringָ�봫���ַ���
��ڲ���: UINT_8 x, UINT_8 y, UINT_8 *string
����ֵ  ����
*********************************************************************/
void display(unsigned char x, unsigned char y, unsigned char *string)
{
    switch (x)
    {
    case 0:
        write_cmd(0x80 + y);
        break;
    case 1:
        write_cmd(0x90 + y);
        break;
    case 2:
        write_cmd(0x88 + y);
        break;
    case 3:
        write_cmd(0x98 + y);
        break;
    default:
        break;
    }
    while (*string != '\0')
    {
        Nop(5);
        write_data(*string);
        string++;
    }
}

void clearTable(unsigned char x)
{
    unsigned char i;
    switch (x)
    {
    case 0:
        write_cmd(0x80);
        break;
    case 1:
        write_cmd(0x90);
        break;
    case 2:
        write_cmd(0x88);
        break;
    case 3:
        write_cmd(0x98);
        break;
    default:
        break;
    }
    for (i = 0; i < 16; i++)
    {
        write_data(0x20);
    }
}