#define CCLK 60000000
#define PCLK CCLK/4
#define LOADVAL ((PCLK)/100000)/2
typedef unsigned char u8;
typedef unsigned int usi;
//I2CONSET BIT CONFIGURATION

#define AA 2
#define SI_BIT 3
#define STOP 4
#define START 5
#define I2C_EN 6
