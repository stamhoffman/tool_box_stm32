#include <stm32f10x_conf.h>

void SysTick_Handler(void) { delay_value++; }

void delay_ms(uint32_t delay_ms) {
  SysTick->VAL = 0;
  delay_value = 0;
  while (delay_value < (delay_ms))
    ;
}

void delay_us_(uint32_t delay_us) {
  int count;
  for (count = 0; count < delay_us; count++);
}


void delay_sec(uint32_t delay_sec)
{
	assert_param(delay_sec > 15);
	int count;
	for (count = 0; count < delay_sec * 1000000; count++);
}


