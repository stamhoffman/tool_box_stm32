#include <stm32f10x_conf.h>

ErrorStatus HSE_ON;
FlagStatus PLL_ON;
RCC_ClocksTypeDef RCC_value;
uint8_t source_clk;

#define QUARZ         //  QUARZ/RC
#define  STM32F103C8T6


void RCC_Config(void);
void GPIO_Config(void);

int main(void)
{

	RCC_Config();
	delay_us(200);
	GPIO_Config();

	LCD_init();
	LCD_print("Hello", 0, 0);


    while(1)
    {
    		GPIO_SetBits(GPIOB,GPIO_Pin_3);
    		delay_us(500);
    		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    		delay_us(500);
    }
}


void GPIO_Config(void) {

  GPIO_InitTypeDef GPIOC_Config;
  GPIOC_Config.GPIO_Pin = CAP_ENTER | CAP_UP_DOWN | CAP_MODE;
  GPIOC_Config.GPIO_Mode = GPIO_Mode_IPD;
  GPIOC_Config.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(PORT_CAP, &GPIOC_Config);

  LCD_setRST(GPIOA, GPIO_Pin_0);
  LCD_setCE(GPIOA, GPIO_Pin_1);
  LCD_setDC(GPIOA, GPIO_Pin_2);
  LCD_setDIN(GPIOA, GPIO_Pin_3);

  GPIO_InitTypeDef LCD_PORT;
  LCD_PORT.GPIO_Pin = GPIO_Pin_All;
  LCD_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
  LCD_PORT.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &LCD_PORT);

  GPIO_InitTypeDef LED;
  LED.GPIO_Pin = GPIO_Pin_3;
  LED.GPIO_Mode = GPIO_Mode_Out_PP;
  LED.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &LED);

}


void RCC_Config(void) {

#ifdef QUARZ
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);

  if ((HSE_ON = RCC_WaitForHSEStartUp()) == SUCCESS) {
    RCC_HCLKConfig(RCC_SYSCLK_Div2);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div16);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);

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

