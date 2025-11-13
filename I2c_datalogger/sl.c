#include<lpc21xx.h>
#include<stdlib.h>
#include"lcd_header.h"
#include"delay.h"
#include"eeprom.c"
#include"i2c.c"
/*void eint1_int(void) __irq
{
	EXTINT=0X02;
	IOCLR0=0X01;
	VICVectAddr=0;	
}*/
//#include"eint1_int.h"	
int main()
{	
	/*lcd_init();
	lcd_cmd(0x80);
	lcd_data('A');*/
	u8 i='0';
	u8 count='0';
	int flag=1;
	IODIR0|=1|0x02;
	IOSET0=1|0x02;
	//interupt_config();
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("Vehicle Count");
	//delay(100);
	lcd_cmd(0xc1);
	lcd_data(count);
	
	i2c_init();
	while(1){
	if(((IOPIN0>>14)&1)==0){
	eeprom_write(0x50,0x00,count);
	eeprom_read(0x50,0x00,i);
	flag=1;
	}
	else if(((IOPIN0>>14)&1)==1)
	{
		   if(flag==1){
		   count++;
		   if(count==58){
		   count='0';
		   i++;
		   if(i==58)
			i=48;
		   }
		   }
		   flag=0;
	}
	if(((IOPIN0>>15)&1)==0)
	{
		IOSET0=1;
		delay(500);
	}
	else
	IOCLR0=1;
	}
	//while(1);

}
