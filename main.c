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

  send.world_1 = 1;
  send.world_2 = 1;
  send.world_3 = 1;
  send.world_4 = 1;

  unpack_world(&send);
#endif

#ifdef DEBAG
  while(1)
  {
		GPIOC -> CRH = 0b00110100010001000100010001000100; // "0" - up_down
		GPIOC -> ODR = 0b0000000000000000;
		delay_us(80);
		GPIOC -> CRH = 0b01000100010001000100010001000100; // "1" - float
		delay_us(80);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		delay_us(10);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
  }
#endif

while (1) {

#ifdef CLIENT
	  dht11();
	  LCD_clrScr();
	  LCD_print("DHT11 sensor", 0, 0);
	  LCD_print("H = ", 0, 2);
	  lcd_out_number(dht11_data.world_1, 20, 2);
	  LCD_print("%", 37, 2);
	  LCD_print("T = ", 0, 3);
	  lcd_out_number(dht11_data.world_3, 20, 3);
	  LCD_print("C", 37, 3);
	  LCD_print("CRC = ", 0, 5);
	  LCD_print(calc_crc(&dht11_data), 25, 5);
	  delay_sec(1);
#endif


#ifdef DEBAG
   //lcd_out_number(dht11_data.world_1, 0, 1);
   //lcd_out_number(dht11_data.world_2, 0, 2);
   //lcd_out_number(dht11_data.world_3, 0, 3);
   //lcd_out_number(dht11_data.world_4, 0, 4);
   //lcd_out_number(dht11_data.world_4, 0, 5);
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

#ifdef DEBAG
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
