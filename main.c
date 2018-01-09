#include <stm32f10x_conf.h>

RCC_ClocksTypeDef RCC_value;
ErrorStatus HSE_ON;
FlagStatus PLL_ON;
uint8_t source_clk;

struct data dht11;


int main(void) {

  RCC_Config();
  GPIO_Config();

  //LCD_init();
  //LCD_print("Tool_Box_STM32", 0, 0);
  //lcd_out_number(RCC_value.HCLK_Frequency, 0, 1);
 //LCD_print("Hz", 50, 1);
  delay_sec(1);

  dht11.number_of_world = 5;
  dht11.bit_order = 8;

  while (1) {
    dht11();
   // LCD_clrScr();
    //LCD_print("DHT11 sensor", 0, 0);
   // LCD_print("H = ", 0, 2);
   // lcd_out_number(dht11.world_1, 20, 2);
   // LCD_print("%", 35, 2);
   // LCD_print("T = ", 0, 3);
    //lcd_out_number(dht11.world_3, 20, 3);
   // LCD_print("C", 35, 3);
    delay_sec(1);
  }
}

void GPIO_Config(void) {

  onewire_port_init(DHTPORT, DHTPIN);

  GPIO_InitTypeDef LCD_PORT;
  LCD_PORT.GPIO_Pin = GPIO_Pin_All;
  LCD_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
  LCD_PORT.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &LCD_PORT);

  //LCD_setRST(GPIOA, GPIO_Pin_0);
  //LCD_setCE(GPIOA, GPIO_Pin_1);
  //LCD_setDC(GPIOA, GPIO_Pin_2);
  //LCD_setDIN(GPIOA, GPIO_Pin_3);
  //LCD_setCLK(GPIOA, GPIO_Pin_4);

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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
}



dht11() {
  start_data_read(DHTPORT, DHTPIN);
  received_data(DHTPORT, DHTPIN);
  pack_world(dht11);
}

void assert_failed(uint8_t *file, uint32_t line) {
  LCD_clrScr();
  lcd_out_number(*(uint32_t *)file, 0, 0);
  lcd_out_number(line, 0, 1);
}
