#include <stm32f10x_conf.h>

GPIO_InitTypeDef Config_DHT;

void dht_port_init(void)
{
	Config_DHT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Config_DHT.GPIO_Pin = DHTPIN;
	Config_DHT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHTPORT,&Config_DHT);
}

void delay_dht(void)
{
	delay_us(1000000);
}

void start_data_read(void)
{
	int count;
	Config_DHT.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(DHTPORT,&Config_DHT);
	delay_us(20);//18 us
	Config_DHT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DHTPORT,&Config_DHT);
	for(count = 0; count < 250; count++) __ASM volatile ("nop");//54us
}

void received_data(void)
{
	int i;
	int count;

	for(count = 0; count < 250; count++) __ASM volatile ("nop");//54us
	for(count = 0; count < 380; count++) __ASM volatile ("nop");//82us

	for(i = 0; i < 40; i++)
	{
		for(count = 0; count < 360; count++) __ASM volatile ("nop");//76us
		if(GPIO_ReadInputDataBit(DHTPORT, DHTPIN))
		{
			data[i] = 1;
		}
		else if(!GPIO_ReadInputDataBit(DHTPORT, DHTPIN))
		{
			data[i] = 0;
		}
		for(count = 0; count < 250; count++) __ASM volatile ("nop");//54us

	}
	for(count = 0; count < 250; count++) __ASM volatile ("nop");//54us
}


void pack_data(void)
{
	LCD_clrScr();
	LCD_print("Start_packed",0,0);
	uint8_t count;
	int bit40_to_struct[40];
	for(count = 0; count < 40; count++)
	{
		bit40_to_struct[count] = data[count];
	}

	dht_data.RH_data_decimal = 0;

	for(count = 0; count < 8; count++)
	{
		dht_data.RH_data_decimal = dht_data.RH_data_decimal | (bit40_to_struct[count] << count);
	}

	dht_data.RH_data_integral = 0;

	for(count = 8; count < 16; count++)
	{
		dht_data.RH_data_integral = dht_data.RH_data_integral | (bit40_to_struct[count] << (count - 8));
	}


	dht_data.T_data_decimal = 0;

	for(count = 16; count < 24; count++)
	{
		dht_data.T_data_decimal = dht_data.T_data_decimal | (bit40_to_struct[count] << (count - 16));
	}

	dht_data.T_data_integral = 0;

	for(count = 24; count < 32; count++)
	{
		dht_data.T_data_integral = dht_data.T_data_integral | (bit40_to_struct[count] << (count - 24));
	}
	LCD_clrScr();
	LCD_print("End_packed",0,0);
}
