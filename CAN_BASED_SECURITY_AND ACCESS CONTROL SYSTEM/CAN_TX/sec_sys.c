#include"can2_driver.c"
#include "header.h"
void delay(int ms)
{
	T0PR=60000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
#include"lcd_header.h"
#include"uart_tx.c"

int main(){	

	CAN2_MSG m1;

	//m2;
	intr_config();

	uart_config();

	can2_init();

	m1.id=0x1AF;

	m1.rtr=0;//data frame

	m1.dlc=4;	

	while(1)

		{
		char str[50]="0600674E634C",str1[50]="0600679AE41F",str2[50]="0600674E6C43";

		can2_tx(m1);

		delay(1000);

	if(strcmp(rfid,str)==0)
	{		
		m1.byteA=0x1;

		m1.byteB=0;

		clear_tag();
	}

	else if(strcmp(rfid,str1)==0)

	{
		m1.byteA=0x1;

		m1.byteB=0;

		clear_tag();
	}
	else if(strcmp(rfid,str2)==0)
	{
		m1.byteA=0x0;

		m1.byteB=0;

		clear_tag();
	}
	else
	{
		m1.byteA=0x5;

		m1.byteB=0;
	}

		}

}

