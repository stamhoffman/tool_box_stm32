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

	uint16_t data[22];


	bmp18c_init(I2C1, 100000, GPIOB, GPIO_Pin_6, GPIO_Pin_7);
	delay_ms(20);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC1, &data[0], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC2, &data[1], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC3, &data[2], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC4, &data[3], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC5, &data[4], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, AC6, &data[5], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, VB1, &data[6], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, VB2, &data[7], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, MB, &data[8], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, MC, &data[9], 0);
	I2C_ReadData(I2C1, BMP18C_ADDRESS, MD, &data[10], 0);

	LCD_clrScr();
	LCD_print("AC1", 0, 0); lcd_out_number(data[0], 20, 0);
	LCD_print("AC2", 0, 1); lcd_out_number(data[1], 20, 1);
	LCD_print("AC3", 0, 2); lcd_out_number(data[2], 20, 2);
	LCD_print("AC4", 0, 3); lcd_out_number(data[3], 20, 3);
	LCD_print("AC5", 0, 4); lcd_out_number(data[4], 20, 4);
	LCD_print("AC6", 0, 5); lcd_out_number(data[5], 20, 5);

	LCD_print("VB1", 40, 0); lcd_out_number(data[0], 60, 0);
	LCD_print("VB2", 40, 1); lcd_out_number(data[1], 60, 1);
	LCD_print("MB", 40, 2); lcd_out_number(data[2], 60, 2);
	LCD_print("MC", 40, 3); lcd_out_number(data[3], 60, 3);
	LCD_print("MD", 40, 4); lcd_out_number(data[4], 60, 4);

   while(1)
   {

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
