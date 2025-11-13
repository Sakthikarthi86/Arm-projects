void interupt_config(void)
{
	VICIntSelect=0;
	VICVectCntl0=0x20|15;
	VICVectAddr0=(unsigned int)eint1_int;

	EXTMODE=0X01;
	EXTPOLAR=0X00;
	VICIntEnable=1<<15;
}
