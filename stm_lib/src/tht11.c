#include <stm32f10x_conf.h>

GPIO_InitTypeDef Config_DHT;



void dht_port_init(void)
{
	Config_DHT.GPIO_Mode = GPIO_Mode_IPU;
	Config_DHT.GPIO_Pin = DHTPIN;
	Config_DHT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHTPORT,&Config_DHT);
	  GPIO_InitTypeDef LED;
	  LED.GPIO_Pin = GPIO_Pin_All;
	  LED.GPIO_Mode = GPIO_Mode_Out_PP;
	  LED.GPIO_Speed = GPIO_Speed_10MHz;
	  GPIO_Init(GPIOB, &LED);

}

void delay_dht(void)
{
	delay_us(1000000);
}

void start_data_read(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	delay_us(30);//30
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	int count;
	for(count = 0; count < 250; count++) __ASM volatile ("nop");//54us 250
	Config_DHT.GPIO_Mode = GPIO_Mode_IPD;
		Config_DHT.GPIO_Pin = GPIO_Pin_5;
		Config_DHT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&Config_DHT);
}

void received_data(void)
{
	int i;
	int count;
	//while(GPIO_ReadInputDataBit(DHTPORT, DHTPIN));
	for(count = 0; count < 250; count++) __ASM volatile ("nop");//54us
	//while(!GPIO_ReadInputDataBit(DHTPORT, DHTPIN));
	for(count = 0; count < 380; count++) __ASM volatile ("nop");//82us

	for(i = 0; i < 40; i++)
	{
		//while(GPIO_ReadInputDataBit(DHTPORT, DHTPIN)); // poka 1 gdem
		for(count = 0; count < 360; count++) __ASM volatile ("nop");//76us
		//while(!GPIO_ReadInputDataBit(DHTPORT, DHTPIN));
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
	//while(!GPIO_ReadInputDataBit(DHTPORT, DHTPIN));
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
