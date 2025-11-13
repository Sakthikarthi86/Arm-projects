#include<lpc21xx.h>
#include<string.h>
#include"i2c.h"

void eeprom_write(u8 slave_addr,u8 data_word_addr,u8 count)
{
	//int i=0,s=0,k=0,rem=0;
	//while(s=(s*10)+k,k=value%10,value/=10);
	i2c_start();
	i2c_write(slave_addr<<1);
	i2c_write(data_word_addr);
	i2c_write(count);
	i2c_stop();
	delay(10);
}
void eeprom_read(u8 slave_addr,u8 data_word_addr,int count)
{
	u8 ch;
	i2c_start();
	i2c_write(slave_addr<<1);
	i2c_write(data_word_addr);
	i2c_restart();
	i2c_write((slave_addr<<1)|1);
	ch=i2c_noack();
	i2c_stop();
		lcd_cmd(0xc0);
	lcd_data(count);
	lcd_cmd(0xc1);
	lcd_data(ch);
}
int page_write(u8 slave_addr,u8 data_word_addr,int value)
{
	int i=0,s,k=0,rem=0;
	while(s=(s*10)+k,k=value%10,value/=10);
	i2c_write(slave_addr<<1);
	while(s)
	{
		i2c_write(data_word_addr+(i++));
		rem=s%10;
		i2c_write(rem+48);
		s/=10;
	}
	i2c_stop();
	delay(10);
	return i;

}
void sequential_read(u8 slave_addr,u8 data_word_addr,int j)
{
	int i;
	unsigned char ch[20];
	i2c_start();
	i2c_write(slave_addr<<1);
	i2c_write(data_word_addr);
	i2c_restart();
	for(i=0;i<j-1;i++){
		i2c_write((slave_addr<<1)|1);
		ch[i]=i2c_masterack();
	}
	ch[i]=i2c_noack();
	i2c_stop();
		delay(100);
		lcd_cmd(0xc0);
	for(i=0;i<j;i++)
	lcd_data(ch[i]+48);
}
