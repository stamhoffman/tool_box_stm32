#include <stm32f10x_conf.h>

void start_data_read(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE) {
  PORT_ONEWIRE->CRH = 0x84444444;
  PORT_ONEWIRE->IDR = 0x00006000;
  delay_ms(18);
  PORT_ONEWIRE->CRH = 0x44444444;
  PORT_ONEWIRE->IDR = 0x0000e000;
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
    delay_us(40);

    if ((PORT_ONEWIRE->IDR & PIN_ONEWIRE)) {
      push_bit(data, bit, 1);
      while (((PORT_ONEWIRE->IDR) & (PIN_ONEWIRE)));
      continue;
    } else {
      push_bit(data, bit, 0);
      continue;
    }
  }
  delay_us(54);
}

void transend_data(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE,struct data *data) {}

void onewire_port_init(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE) {
  GPIO_InitTypeDef Config;
  Config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  Config.GPIO_Pin = PIN_ONEWIRE;
  GPIO_Init(PORT_ONEWIRE, &Config);
}
