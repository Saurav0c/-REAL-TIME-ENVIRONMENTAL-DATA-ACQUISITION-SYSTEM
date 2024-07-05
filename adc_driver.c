   #include<lpc21xx.h>

   void adc_init(void)
  	{
	PINSEL1|=0x15400000;
	ADCR=0x00200400;
	}
	
short int adc_read(char ch)
	{
	short int result=0;
	 ADCR|=1<<ch;
	 ADCR|=1<<24;
	 while(((ADDR>>31)&1)==0);
	 ADCR^=1<<24;
	 ADCR^=1<<ch;
	result=((ADDR>>6)&0x3ff);
	return result;
	}
	
	
	
	
