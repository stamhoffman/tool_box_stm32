#include <stm32f10x_conf.h>

GPIO_InitTypeDef Config_DHT;

void start_data_read(void) {
  DHTPORT->CRH = 0x84444444;
  DHTPORT->IDR = 0x00006000;
  delay_ms(18);
  DHTPORT->CRH = 0x44444444;
  DHTPORT->IDR = 0x0000e000;
  delay_us(8);
}

void received_data(void) {
  int i;

  while ((DHTPORT->IDR) & (DHTPIN));
  delay_us(150);
  while ((DHTPORT->IDR) & (DHTPIN));

  for (i = 0; i < 40; i++) {
    while (!((DHTPORT->IDR) & (DHTPIN)));
   delay_us(40);

    if ((DHTPORT->IDR &DHTPIN)) {
      data[i] = 1;
      while (((DHTPORT->IDR) & (DHTPIN)));
      continue;
    } else {
      data[i] = 0;
      continue;
    }
  }
delay_us(54);
}

void pack_data(void) {
  int count;

  dht_data.RH_data_decimal = 0;

  for (count = 7; count >= 0; count--) {
    dht_data.RH_data_decimal =
        (dht_data.RH_data_decimal) | ((data[count]) << (7 - count));
  }

  dht_data.RH_data_integral = 0;

  for (count = 15; count >= 8; count--) {
    dht_data.RH_data_integral =
        (dht_data.RH_data_integral) | ((data[count]) << (15 - count));
  }

  dht_data.T_data_decimal = 0;

  for (count = 23; count >= 16; count--) {
    dht_data.T_data_decimal =
        (dht_data.T_data_decimal) | ((data[count]) << (23 - count));
  }

  dht_data.T_data_integral = 0;

  for (count = 31; count >= 24; count--) {
    dht_data.T_data_integral =
        (dht_data.T_data_integral) | ((data[count]) << (31 - count));
  }
}

uint8_t bit_shift_calc(uint8_t begin, uint8_t end) {
  uint8_t count;
  uint8_t flag;
  for (count = begin, flag = 0; data[count] == 0 && flag != end;
       count++, flag++)
    ;
  return flag;
}
