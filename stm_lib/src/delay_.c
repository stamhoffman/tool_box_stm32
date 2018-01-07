#include <stm32f10x_conf.h>

RCC_ClocksTypeDef RCC_value;

void SysTick_Handler(void) { delay_value++; }

void delay_ms(uint32_t delay_ms) {
  RCC_GetClocksFreq(&RCC_value);
  SysTick_Config(RCC_value.HCLK_Frequency / 1000);
  SysTick->VAL = 0;
  delay_value = 0;
  while (delay_value < delay_ms);
  SysTick_Config(RCC_value.HCLK_Frequency/1000000);
}

void delay_us(uint32_t delay_us) {
	assert_param(delay_us < 160);
	SysTick->VAL = 0;
	delay_value = 0;
	while (delay_value < delay_us);
}


void delay_sec(uint32_t delay_sec)
{
	RCC_GetClocksFreq(&RCC_value);
	SysTick_Config(RCC_value.HCLK_Frequency/1000);
	SysTick->VAL = 0;
	delay_value = 0;
	while (delay_value < delay_sec * 1000);
	SysTick_Config(RCC_value.HCLK_Frequency / 1000000);
}


