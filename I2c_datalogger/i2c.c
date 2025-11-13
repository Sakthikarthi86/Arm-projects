#include<lpc21xx.h>
#include"i2c.h"
void i2c_init(void)
{
	PINSEL0|=0X50;
	I2SCLL=LOADVAL;
	I2SCLH=LOADVAL;
	I2CONSET=1<<I2C_EN;
}
void i2c_start(void)
{
	I2CONSET=1<<START;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR=1<<START;
}
void i2c_write(u8 addr)
{
	I2DAT=addr;
	I2CONCLR=1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);	
}
void i2c_stop(void)
{
	 I2CONSET=1<<STOP;
	 I2CONCLR=1<<SI_BIT;
}
void i2c_restart(void)
{
	I2CONSET=1<<START;
	I2CONCLR=1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR=1<<START;
}
u8 i2c_noack(void)
{
	I2CONSET=0x00;
	I2CONCLR=1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	return I2DAT;
}
u8 i2c_masterack(void)

{	

	I2CONSET = 0x04; //Assert Ack

  I2CONCLR = 1<<SI_BIT;

	while(((I2CONSET>>SI_BIT)&1)==0);



	I2CONCLR = 0x04; //Clear Assert Ack

 	return I2DAT;

}
