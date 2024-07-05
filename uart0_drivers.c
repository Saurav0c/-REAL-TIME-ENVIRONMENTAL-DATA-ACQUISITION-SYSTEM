#include<lpc21xx.h>
#include"header.h"

void uart0_init(u32 baud)
{
u32 result=0;
int a[]={15,60,30,15,15};
u32 pclk =a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0|=0x5;
U0LCR=0x83;//dlab unlocked
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0x03;//dlab off
}

void uart0_tx(u8 data)
{
 U0THR=data;
 while(((U0LSR>>5)&1)==0);
}

u8 uart0_rx(void)
{
while((U0LSR&1)==0);
return U0RBR;
}
void uart0_tx_string(s8 *ptr)
{
while(*ptr!=0)
{
U0THR=*ptr;
while(((U0LSR>>5)&1)==0);
ptr++;
}
}
void uart0_tx_integer(int num)
{
unsigned int a[10];
int i=0;
if(num==0)
{
uart0_tx('0');
return;
}
if(num<0)
{
num=-num;
uart0_tx('-');
}
while(num>0)
{
a[i]=num%10+48;
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
uart0_tx(a[i]);
}
/*
 void uart0_tx_float(float f)
{
  int j,r;
 if(f==0)
 {
 uart0_tx('0');
 return;
 }
 if(f<0)
 {
  f=-f;
  uart0_tx('-');
 }
 if(f>0)
 {
	j=f;
	uart0_tx_integer(j);
	uart0_tx('.');
	r=(int)(f*100)%100;
	if(r<10)
	{
	uart0_tx('0');
	}
	uart0_tx(r);

 }
 }
 */
void uart0_tx_float(float f)
{
 uart0_tx_integer((int)f);
 uart0_tx('.');
 f=f-((int)f);
 f=f*1000000;
 uart0_tx_integer(f);
}
 






