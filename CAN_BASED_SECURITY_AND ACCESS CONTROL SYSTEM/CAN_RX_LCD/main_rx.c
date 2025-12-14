/* main_nodeB_RX.c */

#include "header.h"
#include"uart_driver.c"
#include"can2_driver.c"
void delay(int ms)
{

	T0PR=60000-1;

	T0TCR=0x01;

	while(T0TC<ms);

	T0TCR=0x03;

	T0TCR=0x00;

}
#include"lcd_header.h"

main(){	

	CAN2_MSG m1;

	lcd_init();

	can2_init();

	uart0_init(115200);

	lcd_cmd(0x80);

	lcd_string("CAN BASED SECURITY AND ACCESS CONTROL SYSTEM");

	while(1){		

		can2_rx(&m1);

		

		if(m1.rtr==0){
					uart0_tx_hex(m1.id);
			uart0_tx(' ');
			uart0_tx_hex(m1.dlc);
			uart0_tx(' ');
			uart0_tx_hex(m1.byteA);
			uart0_tx(' ');
			uart0_tx_hex(m1.byteB);
			uart0_tx_string("\r\n");

			//uart0_tx_string("nodeB: DATA-FRAME is received\r\n");

			if((m1.byteA)==1)
			{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string("Access granted");
				uart0_tx_string("access granted\r\n");
				//delay(1000);
			}
			else if((m1.byteA)==0)
			{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string("Access denied");
				uart0_tx_string("access denied\r\n");
				//delay(1000);
			}
			delay(500);

		}	

		else{

			uart0_tx_string("nodeB: REMOTE-FRAME is received\r\n");

			uart0_tx_hex(m1.id);

			uart0_tx(' ');

			uart0_tx_hex(m1.dlc);

			uart0_tx(' ');

			uart0_tx_string("\r\n");

		}	

	}

	

}

