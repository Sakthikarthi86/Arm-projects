/* main_nodeB_RX.c */
#include<lpc21xx.h>
#define motor1 1<<14

#define motor2 1<<15
void delay(int ms)

{

	T0PR=60000-1;

	T0TCR=0x01;

	while(T0TC<ms);

	T0TCR=0x03;

	T0TCR=0x00;

}
#include "header.h"
#include"uart_driver.c"
#include"can2_driver.c"

main(){	
	CAN2_MSG m1;

	IODIR0|=1<<8|motor1;
	IOSET0=1<<8;

	can2_init();

	uart0_init(115200);

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

			if((m1.byteA)==1)

			{
				IOSET0=motor1;

				delay(1000);

				IOCLR0=motor1;

			}

			else if((m1.byteA)==0)

			{
				IOCLR0=1<<8;
				delay(2000);
				IOSET0=1<<8;

				//IOSET0=motor2;

		 		//IOCLR0=motor1;

			}

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

