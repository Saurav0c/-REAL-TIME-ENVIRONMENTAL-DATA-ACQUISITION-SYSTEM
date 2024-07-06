//MCP3204 EXTERNAL ADC 

#include<lpc21xx.h>
#include"header.h"
#define CSO (1<<7)
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
  