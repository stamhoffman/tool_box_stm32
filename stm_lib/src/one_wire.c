#include <stm32f10x_conf.h>

void start_data_read(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE) {
  GPIOC -> CRH = 0b00110100010001000100010001000100; // "0" -in  down
  GPIOC -> ODR = 0b0000000000000000;
  delay_ms(18);
  GPIOC -> CRH = 0b01000100010001000100010001000100; // "1" - float
  delay_us(8);
}

void received_data(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE, struct data *data) {

  #define NUMBER_BIT data->number_of_world * data->number_of_world

  while ((PORT_ONEWIRE->IDR) & (PIN_ONEWIRE));
  delay_us(150);
  while ((PORT_ONEWIRE->IDR) & (PIN_ONEWIRE));

  uint8_t bit;
  for (bit = 0; bit < NUMBER_BIT; bit++) {
    while (!((PORT_ONEWIRE->IDR) & (PIN_ONEWIRE)));
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
    delay_us(40);
    if ((PORT_ONEWIRE->IDR & PIN_ONEWIRE)) {
      push_bit(data, bit, 1);
      while (((PORT_ONEWIRE->IDR) & (PIN_ONEWIRE)));
      continue;
    } else {
      push_bit(data, bit, 0);
      continue;
    }
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
  }
  delay_us(54);
}

void start_data_send(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE)
{
	delay_ms(17);
	if((PORT_ONEWIRE->IDR) & (PIN_ONEWIRE)) return;
	while (!((PORT_ONEWIRE->IDR) & (PIN_ONEWIRE)));
    delay_us(8);
    GPIOC -> CRH = 0b00110100010001000100010001000100; // "0" -in  down
    GPIOC -> ODR = 0b0000000000000000;
	delay_us(80);
	GPIOC -> CRH = 0b01000100010001000100010001000100; // "1" - float
	delay_us(80);
}

void transend_data(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE,struct data *data)
{
    #define NUMBER_BIT_TR data->bit_order * data->number_of_world
	int bit;
	int cyr_bit;
	for(bit = 0; bit < NUMBER_BIT_TR; bit++)
	{
		GPIOC -> CRH = 0b00110100010001000100010001000100; // "0" -in  down
		GPIOC -> ODR = 0b0000000000000000;
		delay_us(50);
		GPIOC -> CRH = 0b01000100010001000100010001000100; // "1" - float
		cyr_bit = pop_bit(data, bit);
		if(cyr_bit == 1)
		{
			delay_us(70);
			continue;
		}
		else
		{
			delay_us(27);
			continue;
		}
	}
}

void onewire_port_init(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE) {

#ifdef CLIENT
	GPIOC -> CRH = 0b10000100010001000100010001000100; // "15 bit" - float
	GPIOC -> ODR = 0b1000000000000000;
	delay_sec(1);
#endif

#ifdef SERVER
	GPIOC -> CRH = 0b10000100010001000100010001000100; // "15 bit" - float
	GPIOC -> ODR = 0b1000000000000000;
	delay_sec(1);
#endif

#ifdef DEBAG
	GPIOC -> CRH = 0b01001000010001000100010001000100; // "15 bit" - float
	GPIOC -> ODR = 0b0100000000000000;
	delay_sec(1);
#endif

}
