#include <stm32f10x_conf.h>

volatile void SysTick_Handler(void) { delay_value++; }

volatile void delay_us(uint32_t delay_us) {
  SysTick->VAL = 0;
  delay_value = 0;
  while (delay_value < (delay_us - 10));
}

volatile void delay_us_(uint32_t delay_us)
{
	int count;
	for(count = 0; count < delay_us; count++);

}
