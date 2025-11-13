//I2C DECLARATION
void i2c_init(void);
void i2c_start(void);
void i2c_write(u8);
void i2c_stop(void);
void i2c_restart(void);
u8 i2c_noack(void);
u8 i2c_masterack(void);

//EEPROM DECLARATION
void eeprom_write(u8,u8,u8);
void eeprom_read(u8,u8,int);
int page_write(u8,u8,int);
void sequential_read(u8,u8,int);

//DELAY HEADER
void delay(int);
//LCD HEADERS
void lcd_init(void);
void lcd_cmd(u8);
void lcd_data(u8);
void lcd_string(u8 *);
