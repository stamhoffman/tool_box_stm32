#include <stm32f10x_conf.h>

#pragma pack(push,1)

struct data {
  uint8_t number_of_world;
  uint8_t bit_order;
  int world_1;
  int bit_0 : 1;
  int bit_1 : 1;
  int bit_2 : 1;
  int bit_3 : 1;
  int bit_4 : 1;
  int bit_5 : 1;
  int bit_6 : 1;
  int bit_7 : 1;
  int world_2;
  int bit_8 : 1;
  int bit_9 : 1;
  int bit_10 : 1;
  int bit_11 : 1;
  int bit_12 : 1;
  int bit_13 : 1;
  int bit_14 : 1;
  int bit_15 : 1;
  int world_3;
  int bit_16 : 1;
  int bit_17 : 1;
  int bit_18 : 1;
  int bit_19 : 1;
  int bit_20 : 1;
  int bit_21 : 1;
  int bit_22 : 1;
  int bit_23 : 1;
  int world_4;
  int bit_24 : 1;
  int bit_25 : 1;
  int bit_26 : 1;
  int bit_27 : 1;
  int bit_28 : 1;
  int bit_29 : 1;
  int bit_30 : 1;
  int world_5;
  int bit_31 : 1;
  int bit_32 : 1;
  int bit_33 : 1;
  int bit_34 : 1;
  int bit_35 : 1;
  int bit_36 : 1;
  int bit_37 : 1;
  int bit_38 : 1;
  int bit_39 : 1;
};

#pragma pack(pop)

void pack_world(struct data *data);
void calc_crc(struct data *data);
void push_bit(struct data *data, uint8_t bit, int value);
void output_data(struct data *data, uint8_t bit);
