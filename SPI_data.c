#include<lpc21xx.h>
#define CSO (1<<7)
void spi0_init(void)
{
 PINSEL0|=0x1500;
 IODIR0|=CSO;
 IOSET0|=CSO;
 S0SPCCR=15;
 S0SPCR=0x20;
}
unsigned char spi0_data(unsigned char data)
{
 S0SPDR=data;
 while(((S0SPSR>>7)&1)==0);
return S0SPDR;
}
unsigned short int MCP3204_adc_read(char ch)
{
unsigned char lbyte,hbyte;
 unsigned short int result=0;
 ch=ch<<6;
 IOCLR0=CSO;
 spi0_data(0x06);
 hbyte=spi0_data(ch);
 lbyte=spi0_data(0x0);
 IOSET0=CSO;
 hbyte=hbyte&0x0f;
 result=(hbyte<<8)|lbyte;
 return result;
}
