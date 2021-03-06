#include <stm32f10x_conf.h>

RCC_ClocksTypeDef RCC_value;
ErrorStatus HSE_ON;
FlagStatus PLL_ON;
uint8_t source_clk;

struct data dht11_data;
struct data send;

int main(void) {

  RCC_Config();
  GPIO_Config();

  LCD_init();
  LCD_print("Tool_Box_STM32", 0, 0);
  lcd_out_number(RCC_value.HCLK_Frequency, 0, 1);
  LCD_print("Hz", 50, 1);


#ifdef CLIENT
  dht11_data.number_of_world = 5;
  dht11_data.bit_order = 8;
#endif

#ifdef SERVER
  send.number_of_world = 5;
  send.bit_order = 8;

  send.world_1 = 20;
  send.world_2 = 20;
  send.world_3 = 20;
  send.world_4 = 20;

  unpack_world(&send);
#endif

#ifdef DEBUG


#endif


while (1) {

#ifdef CLIENT
	  dht11();
	  LCD_clrScr();
	  LCD_print("DHT11 sensor", 0, 0);
	  LCD_print("H = ", 0, 2);
	  lcd_out_number(dht11_data.world_1, 20, 2);
	  LCD_print("%", 38, 2);
	  LCD_print("T = ", 0, 3);
	  lcd_out_number(dht11_data.world_3, 20, 3);
	  LCD_print("C", 38, 3);
	  LCD_print("CRC = ", 0, 5);
	  LCD_print(calc_crc(&dht11_data), 25, 5);
	  delay_sec(1);
#endif


#ifdef DEBUG

	uint8_t data[27];

	bmp18c_init(I2C1, 100000, GPIOB, GPIO_Pin_6, GPIO_Pin_7);
	delay_ms(20);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC1, &data[0], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC1_, &data[1], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC2, &data[2], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC2_, &data[3], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC3, &data[4], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC3_, &data[5], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC4, &data[6], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC4_, &data[7], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC5, &data[8], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC5_, &data[9], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC6, &data[10], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC6_, &data[11], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, VB1, &data[12], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, VB1_, &data[13], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, VB2, &data[14], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, VB2_, &data[15], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, MB, &data[16], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, MB_, &data[17], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, MC, &data[18], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, MC_, &data[19], 0);

	I2C_ReadData(I2C1, BMP18C_ADDRESS, MD, &data[20], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, MD_, &data[21], 0);

	short ac1 = (data[0] << 8) | data[1];
	short ac2 = (data[2] << 8) |data[3];
	short ac3 = (data[4] << 8) |data[5];
	unsigned short ac4 = (data[6] << 8) | data[7];
	unsigned short ac5 = (data[8] << 8) | data[9];
	unsigned short ac6 = (data[10] << 8) | data[11];
	short vb1 = (data[12] << 8) | data[13];
	short vb2 = (data[14] << 8) | data[15];
	short mb = (data[16] << 8) | data[17];
	short mc = (data[18] << 8) | data[19];
	short md = (data[20] << 8) | data[21];

	long temp;
	long prescure;


	while(1)
   {
		I2C_WriteData(I2C1, BMP18C_ADDRESS, TEMP_CR, TEMP_CR_VAL);
			delay_ms(100);
			I2C_ReadData(I2C1, BMP18C_ADDRESS, TEMP, &data[22], 1);
			I2C_ReadData(I2C1, BMP18C_ADDRESS, TEMP_, &data[23], 1);

			I2C_WriteData(I2C1, BMP18C_ADDRESS, PRESCURE_CR, PRESCURE_CR_VAL);
			delay_ms(100);
			I2C_ReadData(I2C1, BMP18C_ADDRESS, PRESCURE, &data[24], 1);
			I2C_ReadData(I2C1, BMP18C_ADDRESS, PRESCURE_, &data[25], 1);
			I2C_ReadData(I2C1, BMP18C_ADDRESS, PRESCURE_A, &data[26], 1);

			int oss = 0;
			temp = (data[22] << 8) + data[23];
			prescure = (data[24]<<16 + data[25]<<8 + data[26]) >> (8 - oss);

			double X1 = (temp - ac6) * ac5 / 32768;
			double X2 = mc * 2048 / (X1 + md);
			double B5 = X1 + X2;
			double T = (B5 + 8) / 16;
			int Cel = T;
			int Des = (int)((T - Cel) * 100.0);

			LCD_clrScr();
			LCD_print("BMP18C_sensor", 0, 0);
			LCD_print("TEMP =", 0, 1); lcd_out_number(Cel, 40, 1);LCD_print(",", 52, 1); lcd_out_number(Des, 57, 1); LCD_print("C", 70, 1);

			long B6 = B5 - 4000;
			X1 = (VB2 * (B6 * B6 / 4096)) / 2048;
			X2 = (ac2 * B6) / 2048;
			long X3 = (X1 + X2);
			long B3 = ((ac1 * 4 + X3) << oss + 2)/ 4;
			X1 = AC3 * B6 / 8192;
			X2 = (vb1 * (B6 * B6 / 4096 )) / 65536;
			X3 = ((X1 + X2) + 2) / 4;
			unsigned long B4 = ac4 * (unsigned long)(X3 + 32768) / 32768;
			unsigned long B7 = ((unsigned long)prescure - B3) * (50000 >> oss);
			long P;
			if (B7 < 0x80000000) P = (B7 * 2) / B4;
			else P = (B7 / B4) * 2;
			X1 = (P / 256 ) * (P / 256 );
			X1 = (X1 * 3038) / 65536;
			X2 = (-7357 * P) / 65536;
			P = P + (X1 + X2 + 3791) / 16;


			LCD_print("PRESSURE", 0, 2);
			LCD_print("P =", 0, 3); lcd_out_number(P, 20, 3);LCD_print(",", 57, 3); lcd_out_number(Des, 62, 3); LCD_print("P", 74, 3);

   }

#endif

#ifdef SERVER
   while (((DHTPORT->IDR) & (DHTPIN)));
   send_onewire();
#endif
  }
}

void GPIO_Config(void) {

#ifdef CLIENT
  onewire_port_init(DHTPORT, DHTPIN);
#endif

#ifdef SERVER
  onewire_port_init(DHTPORT, DHTPIN);
#endif

#ifdef DEBUG
  onewire_port_init(DHTPORT,DHTPIN);
#endif

  GPIO_InitTypeDef LCD_PORT;
  LCD_PORT.GPIO_Pin = GPIO_Pin_All;
  LCD_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
  LCD_PORT.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &LCD_PORT);

  LCD_setRST(GPIOA, GPIO_Pin_0);
  LCD_setCE(GPIOA, GPIO_Pin_1);
  LCD_setDC(GPIOA, GPIO_Pin_2);
  LCD_setDIN(GPIOA, GPIO_Pin_3);
  LCD_setCLK(GPIOA, GPIO_Pin_4);

  GPIO_InitTypeDef CLK_PIN;

  CLK_PIN.GPIO_Mode = GPIO_Mode_Out_PP;
  CLK_PIN.GPIO_Pin = GPIO_Pin_5;
  CLK_PIN.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &CLK_PIN);
}

void RCC_Config(void) {

#ifdef QUARZ
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);

  if ((HSE_ON = RCC_WaitForHSEStartUp()) == SUCCESS) {
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div16);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08)
      ;

    RCC_ClockSecuritySystemCmd(ENABLE);
  }
#endif

  RCC_GetClocksFreq(&RCC_value);
  SysTick_Config(RCC_value.HCLK_Frequency / 1000);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}

void dht11(void) {
  start_data_read(DHTPORT, DHTPIN);
  received_data(DHTPORT, DHTPIN, &dht11_data);
  pack_world(&dht11_data);
}

void send_onewire(void)
{
	start_data_send(DHTPORT, DHTPIN);
	transend_data(DHTPORT, DHTPIN,&send);
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line) {
   LCD_clrScr();
   lcd_out_number(*(uint32_t *)file, 0, 0);
   lcd_out_number(line, 0, 1);
 }
#endif
