#define lcd_d1 0xf<<10

#define rs 1<<8

#define E 1<<9

void lcd_init(void);

void lcd_cmd(unsigned char);

void lcd_data(unsigned char);

void delay(int);


void lcd_init(void)

{

	IODIR0 |=lcd_d1|rs|E;

	lcd_cmd(0x01);

	lcd_cmd(0x02);

	lcd_cmd(0x0c);

	lcd_cmd(0x28);

	lcd_cmd(0x80);

}

void lcd_cmd(unsigned char cmd)

{

	IOCLR0=lcd_d1;

	IOSET0=(0xf0&cmd)<<6;

	IOCLR0=rs;

	IOSET0=E;

	delay(2);

	IOCLR0=E;


	IOCLR0=lcd_d1;

	IOSET0=(0xf&cmd)<<10;

	IOCLR0=rs;

	IOSET0=E;

	delay(2);

	IOCLR0=E;

}

void lcd_data(unsigned char d)

{

	IOCLR0=lcd_d1;

	IOSET0=(0xf0&d)<<6;

	IOSET0=rs;

	IOSET0=E;

	delay(2);

	IOCLR0=E;


	IOCLR0=lcd_d1;

	IOSET0=(0xf&d)<<10;

	IOSET0=rs;

	IOSET0=E;

	delay(2);

	IOCLR0=E;

}

void lcd_string(unsigned char *s)

{

	while(*s)

	{

		lcd_data(*s++);

	}

}
