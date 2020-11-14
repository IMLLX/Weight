#include "weigh.h"
#define LCD_BUS P0 // 12864液晶接口总线

sbit LCD_RS = P3 ^ 5;  // 低电平为写指令，高电平为写数据端
sbit LCD_RW = P3 ^ 6;  // 低电平为写，高电平为读
sbit LCD_EN = P3 ^ 4;  // 使能端
sbit LCD_PSB = P3 ^ 7; // 对比度
sbit busy = P0 ^ 7;    // 忙端口



/********************************************************************
函数名称: void Check_Busy()		
功能简介: 读检测12864液晶内部工作状态
入口参数: 无
返回值  ：无
*********************************************************************/
void await_lcd()
{
    LCD_BUS = 0xff; // 把LCD_BUS拉高为输入端
    LCD_RS = 0;
    LCD_RW = 1; // 读
    LCD_EN = 1;
    delay(5);
    while ((LCD_BUS & 0x80) == 0x80)
        ; // LCD_BUS最高位为STA7返回值，0允许操作，1禁止
    // while (!LCD_BUS);
    while (busy)
        ;
    LCD_EN = 0;
}

/********************************************************************
函数名称: void write_cmd(unsigned char cmd)	
功能简介: 12864液晶写指令
入口参数: UINT_8 cmd
返回值  ：无
*********************************************************************/
void write_cmd(unsigned char cmd)
{
    await_lcd();
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    LCD_BUS = cmd;
    LCD_EN = 1; //在使能端LCD_EN上升沿时把指令cmd写入
    Nop(3);
    LCD_EN = 0;
}

/********************************************************************
函数名称: void write_data(unsigned char dat)
功能简介: 12864液晶写数据
入口参数: UINT_8 data
返回值  ：无
*********************************************************************/
void write_data(unsigned char dat)
{
    await_lcd();
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_BUS = dat;
    LCD_EN = 1;
    Nop(3);
    LCD_EN = 0;
}

/********************************************************************
函数名称: dis_init()
功能简介: 12864液晶初始化
入口参数: 无
返回值  ：无
*********************************************************************/
void dis_init()
{
    // write_cmd(0x30);    // 8为并行，指令为基本指令
    write_cmd(0x0c); // 显示开
    write_cmd(0x01); // 清屏
    write_cmd(0x06); // 光标移动方向
}

/********************************************************************
函数名称: void display(unsigned char x, unsigned char y, unsigned char *string)	
功能简介: 液晶DDRAM地址选择显示,x选择行，y选择列，string指针传递字符串
入口参数: UINT_8 x, UINT_8 y, UINT_8 *string
返回值  ：无
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
        write_data(*string);
        string++;
    }
}