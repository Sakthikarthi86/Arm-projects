#include<lpc21xx.h>

#include<string.h>

void uart_config(void);

void intr_config(void);

void uart_tx(char);

void clear_tag(void);

int i=0,j;

char rfid[20];

void isr(void) __irq

{

	 rfid[i++]=U0RBR;

	 rfid[i]='\0';

	 //uart_tx((char)i+48);

	 if(i==12){

	for(j=0;j<i;j++)

	uart_tx(rfid[j]);

	}

	 VICVectAddr=0;

}
void clear_tag()

{

	int j=0;

	for(;j<i;j++)

	{

		rfid[j]='\0';

	}

	i=0;

}

void intr_config(void)

{

	VICIntSelect=0;

	VICVectCntl0=0x20|6;

	VICVectAddr0=(unsigned long)isr;

	EXTMODE=0X01;

	EXTPOLAR=0X00;

	VICIntEnable=1<<6;

}

void uart_config(void)

{
	PINSEL0|=0X05;

	U0LCR=0X83;

	U0DLL=134;

	U0DLM=1;

	U0LCR=0X03;

	U0IER=1;

}

void uart_tx(char tran)

{

	U0THR=tran;

	while(((U0LSR>>5)&1)==0);

}
