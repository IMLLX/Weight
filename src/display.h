#ifndef _DISPLAY_
#define _DISPLAY_


extern void dis_init();
extern void display(unsigned char x, unsigned char y, char *string);
extern void await_lcd();


void write_cmd(unsigned char);
void write_data(unsigned char);


#endif