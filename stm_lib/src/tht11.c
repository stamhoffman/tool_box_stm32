#include <stm32f10x_conf.h>

GPIO_InitTypeDef Config_DHT;


void start_data_read(void)
{
	LCD_clrScr();
	LCD_print("read_data",0,0);
	int count;
	DHTPORT ->CRH = 0x84444444;
	DHTPORT -> IDR = 0x00006000;
	delay_us(25);
	DHTPORT ->CRH = 0x44444444;
	DHTPORT -> IDR = 0x0000e000;
	for(count = 0; count < 70; count++) __ASM volatile ("nop");//35us
}

void received_data(void)
{
	int i;
	int bit = 0;
	int count;
	for(count = 0; count < 920; count++) __ASM volatile ("nop");//82us
	//lcd_out_number((DHTPORT->IDR) & (DHTPIN) << 15,0,3);
	while((DHTPORT->IDR) & (DHTPIN));//poka 1

	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);

	for(i = 0; i < 40; i++)
	{
		while(!((DHTPORT->IDR) & (DHTPIN)));//poka 0
		for(count = 0; (bit = ((DHTPORT->IDR) & (DHTPIN))) && count < 70; count++) __ASM volatile ("nop");//us

		if(GPIO_ReadInputDataBit(DHTPORT,DHTPIN))
		{
			data[i] = 1;
			while(((DHTPORT->IDR) & (DHTPIN)));
			continue;
		}
		else
		{
			data[i] = 0;
			continue;
		}
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
