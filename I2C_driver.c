
#include <LPC21xx.H>
#include "header.h"
#define si ((I2CONSET>>3)&1)
void i2c_init(void)
{
	PINSEL0|=0x50;//p0.2 & p0.3 (SCL SDA)
	I2SCLL=I2SCLH=75;
  I2CONSET=(1<<6);
}

void i2c_byte_write_frame(unsigned char sa,unsigned char mr,unsigned char data)
{
	/////////////////////////start///////////////////////
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(si==0);
	I2CONCLR=(1<<5);
	if(I2STAT!=0x08)
	{
		uart0_tx_string("ERR : start  \r\n");
		goto exit;
	}
	
	/////////////////////////sa+w///////////////////////
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(si==0);
	if(I2STAT==0x20)
	{
		uart0_tx_string("ERR : sa+w  \r\n");
		goto exit;
	}
	
	/////////////////////////mr///////////////////////
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(si==0);
	if(I2STAT==0x30)
	{
		uart0_tx_string("ERR : mr \r\n");
		goto exit;
	}
	
	/////////////////////////data///////////////////////
	I2DAT=data;
	I2CONCLR=(1<<3);
	while(si==0);
	if(I2STAT==0x30)
	{
		uart0_tx_string("ERR : data  \r\n");
		goto exit;
	}
	
	
	exit :
	 I2CONCLR=1<<3;
 	 I2CONSET=1<<4;
	
}

unsigned char i2c_byte_read_frame(unsigned char sa,unsigned mr)
{
	
	unsigned char result;
	
	/////////////////////////start///////////////////////
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(si==0);
	I2CONCLR=(1<<5);
	if(I2STAT!=0x08)
	{
		uart0_tx_string("ERR : start  \r\n");
		goto exit;
	}
	
	/////////////////////////sa+w///////////////////////
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(si==0);
	if(I2STAT==0x20)
	{
		uart0_tx_string("ERR : sa+w  \r\n");
		goto exit;
	}
	
	/////////////////////////mr///////////////////////
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(si==0);
	if(I2STAT==0x30)
	{
		uart0_tx_string("ERR : mr \r\n");
		goto exit;
	}
		/////////////////////////restart///////////////////////
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(si==0);
	I2CONCLR=(1<<5);
	if(I2STAT!=0x10)
	{
		uart0_tx_string("ERR : start  \r\n");
		goto exit;
	}
	
	/////////////////////////sa+r///////////////////////
	I2DAT=sa|1;
	I2CONCLR=(1<<3);
	while(si==0);
	if(I2STAT==0x48)
	{
		uart0_tx_string("ERR : sa+2  \r\n");
		goto exit;
	}
	
	////////////////////result///////////////
	I2CONCLR=1<<3;
	while(si==0);
	result=I2DAT;
	
	exit :
	 I2CONCLR=1<<3;
 	 I2CONSET=1<<4;
	return result;
	
}








































































/*
#include<lpc21xx.h>
#include"header.h"
#define SI ((I2CONSET>>3)&1)
void i2c_init(void)
{
PINSEL0|=0x50;
I2SCLH=I2SCLL=75;
I2CONSET=(1<<6);
}
void i2c_byte_write_frame(unsigned char sa,unsigned char mr,unsigned char data)
{
/////////////////////
I2CONSET=1<<5;
I2CONCLR=1<<3;
while(SI==0);
I2CONCLR=1<<5;
if(I2STAT!=0x8)
{
uart0_tx_string("ERROR STARTING\r\n");
goto exit;
}
///////////////////////
I2DAT=sa;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==0x20)
{
uart0_tx_string("ERROR SA+w \r\n");
goto exit;
}

I2DAT=mr;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==0x30)
{
uart0_tx_string("ERROR mr \r\n");
goto exit;
}
I2DAT=data;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==0x30)
{
uart0_tx_string("ERROR data \r\n");
goto exit;
}

exit:
I2CONSET=1<<4;
I2CONCLR=1<<3;
}

unsigned char i2c_byte_read_frame(unsigned char sa,unsigned mr)
{
unsigned char temp;
I2CONSET=1<<5;
I2CONCLR=1<<3;
while(SI==0);
I2CONCLR=1<<5;
if(I2STAT!=0x8)
{
uart0_tx_string("ERROR STARTING\r\n");
goto exit;
}

I2DAT=sa;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==0x20)
{
uart0_tx_string("ERROR SA+W \r\n");
goto exit;
}

I2DAT=mr;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==0x30)
{
uart0_tx_string("ERROR mr \r\n");
goto exit;
}
I2CONSET=1<<5;
I2CONCLR=1<<3;
while(SI==0);
I2CONCLR=1<<5;
if(I2STAT!=0x10)
{
uart0_tx_string("ERROR RESTARTING\r\n");
goto exit;
}
I2DAT=sa|1;
I2CONCLR=1<<3;
while(SI==0);
if(I2STAT==0x48)
{
uart0_tx_string("ERROR SA+R \r\n");
goto exit;
}

I2CONCLR=1<<3;
while(SI==0);
temp=I2DAT;

exit:
I2CONSET=1<<4;
I2CONCLR=1<<3;

return temp;


}

  */


