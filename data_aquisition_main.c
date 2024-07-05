#include<LPC21XX.H>
#include"header.h"
main()
{
unsigned char h,m,d,mi,y,h1;
float temperature,vout;
unsigned short int temp;
unsigned int temp1,a;

uart0_init(9600);
lcd_init();
adc_init();
spi0_init();
i2c_init();
i2c_byte_write_frame(0xD0,0x01,0x59);
i2c_byte_write_frame(0xD0,0x02,0x51);


i2c_byte_write_frame(0xD0,0x04,0x04);
i2c_byte_write_frame(0xD0,0x05,0x07);
i2c_byte_write_frame(0xD0,0x06,0x24);
while(1)
{
mi=i2c_byte_read_frame(0xD0,0x01);
h=i2c_byte_read_frame(0xD0,0x02);

d=i2c_byte_read_frame(0xD0,0x04);
m=i2c_byte_read_frame(0xD0,0x05);
y=i2c_byte_read_frame(0xD0,0x06);

lcd_cmd(0xc8);
lcd_data((d/0x10)+48);
lcd_data((d%0x10)+48);
lcd_data('/');
lcd_data((m/0x10)+48);
lcd_data((m%0x10)+48);
lcd_data('/');
lcd_data((y/0x10)+48);
lcd_data((y%0x10)+48);


lcd_cmd(0xc0); 
h1=h&0x1f;
lcd_data((h1/0x10)+48);
lcd_data((h1%0x10)+48);
lcd_data(':');
lcd_data((mi/0x10)+48);
lcd_data((mi%0x10)+48);
if((h>>5&1)==1)
{
lcd_string("PM");
}
else
{
lcd_string("AM");
}
temp=adc_read(1);
vout=(temp*3.3)/1023;
temperature=(vout-0.5)/0.01;
lcd_cmd(0x80);//ambient temperature
lcd_string("Temp:");
lcd_integer(temperature);
delay_ms(100);

temp1=MCP3204_adc_read(2);
//a=temp1;
//a=(a/4095)*100;
a=100-((temp1*100)/4095);
lcd_cmd(0x88);
lcd_string("light");
lcd_data(a/10+48);
lcd_data(a%10+48);
lcd_data('%');
delay_ms(300);
}
}
