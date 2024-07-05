#include<LPC21xx.H>
#include"header.h"
void lcd_data(unsigned char data)
{
unsigned int temp;
IOCLR1=	0x00FE0000;
temp=(data&0xF0)<<16;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0x00FE0000;
temp=(data&0x0F)<<20;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_cmd(unsigned int cmd)
{
unsigned int temp;
IOCLR1=0X00FE0000;
temp=(cmd&0xF0)<<16;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0x00FE0000;
temp=(cmd&0x0F)<<20;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}
void lcd_init(void)
{
IODIR1|=0x00FE0000;
PINSEL2=0;
IOCLR1=1<<19;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0e);
}
void lcd_string(unsigned char *ptr)
{
while(*ptr!=0)
{
lcd_data(*ptr);
ptr++;
}
}
void lcd_integer(int num)
{
int a[10],i;
if(num==0)
{
lcd_data('0');
return;
}
if(num<0)
{
num=-num;
lcd_data('-');
}
i=0;
while(num>0)
{
a[i]=(num%10)+48;
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
lcd_data(a[i]);
}

void lcd_float(float f)
{
lcd_integer((int)f);
lcd_data('.');
f=f-((int)f);
f=f*1000;
lcd_integer(f);


}
























