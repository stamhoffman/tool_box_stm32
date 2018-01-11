#include <stm32f10x_conf.h>

void pack_world(struct data *data) {
  if (data-> number_of_world >= 1)
    memcpy(&data->world_1, &data->world_1 + 1, sizeof(char));
  if (data -> number_of_world >= 2)
    memcpy(&data->world_2, &data->world_2 + 1, sizeof(char));
  if (data -> number_of_world >= 3)
    memcpy(&data->world_3, &data->world_3 + 1, sizeof(char));
  if (data -> number_of_world >= 4)
    memcpy(&data->world_4, &data->world_4 + 1, sizeof(char));
  if (data -> number_of_world >= 5)
    memcpy(&data->world_5, &data->world_5 + 1, sizeof(char));
}

void calc_crc_world(struct data *data) {
  if (data-> number_of_world >= 1)
    ;
  if (data-> number_of_world >= 2)
    ;
  if (data-> number_of_world >= 3)
    data-> world_3 = (data-> world_1 | data-> world_2);
  if (data-> number_of_world >= 4)
    data-> world_4 = (data-> world_1 | data-> world_2 | data-> world_3);
  if (data-> number_of_world >= 5)
    data-> world_5 = (data-> world_1 | data-> world_2 | data-> world_3 | data-> world_4);
}

void push_bit(struct data *data, uint8_t bit, int value)
{

  if(bit == 0) data-> bit_7 = value;
  if(bit == 1) data-> bit_6 = value;
  if(bit == 2) data-> bit_5 = value;
  if(bit == 3) data-> bit_4 = value;
  if(bit == 4) data-> bit_3 = value;
  if(bit == 5) data-> bit_2 = value;
  if(bit == 6) data-> bit_1 = value;
  if(bit == 7) data-> bit_0 = value;
  if(bit == 8) data-> bit_15 = value;
  if(bit == 9) data-> bit_14 = value;
  if(bit == 10) data-> bit_13 = value;
  if(bit == 11) data-> bit_12 = value;
  if(bit == 12) data-> bit_11 = value;
  if(bit == 13) data-> bit_10 = value;
  if(bit == 14) data-> bit_9 = value;
  if(bit == 15) data-> bit_23 = value;
  if(bit == 16) data-> bit_22 = value;
  if(bit == 17) data-> bit_21 = value;
  if(bit == 18) data-> bit_20 = value;
  if(bit == 19) data-> bit_19 = value;
  if(bit == 20) data-> bit_18 = value;
  if(bit == 21) data-> bit_17 = value;
  if(bit == 22) data-> bit_16 = value;
  if(bit == 23) data-> bit_31 = value;
  if(bit == 24) data-> bit_30 = value;
  if(bit == 25) data-> bit_29 = value;
  if(bit == 26) data-> bit_28 = value;
  if(bit == 27) data-> bit_27 = value;
  if(bit == 28) data-> bit_26 = value;
  if(bit == 29) data-> bit_25 = value;
  if(bit == 30) data-> bit_24 = value;
  if(bit == 31) data-> bit_31 = value;
  if(bit == 32) data-> bit_30 = value;
  if(bit == 33) data-> bit_29 = value;
  if(bit == 34) data-> bit_28 = value;
  if(bit == 35) data-> bit_27 = value;
  if(bit == 36) data-> bit_26 = value;
  if(bit == 37) data-> bit_25 = value;
  if(bit == 38) data-> bit_24 = value;
  if(bit == 39) data-> bit_23 = value;

/*
  if(bit == 0) data-> bit_0 = value;
  if(bit == 1) data-> bit_1 = value;
  if(bit == 2) data-> bit_2 = value;
  if(bit == 3) data-> bit_3 = value;
  if(bit == 4) data-> bit_4 = value;
  if(bit == 5) data-> bit_5 = value;
  if(bit == 6) data-> bit_6 = value;
  if(bit == 7) data-> bit_7 = value;
  if(bit == 8) data-> bit_8 = value;
  if(bit == 9) data-> bit_9 = value;
  if(bit == 10) data-> bit_10 = value;
  if(bit == 11) data-> bit_11 = value;
  if(bit == 12) data-> bit_12 = value;
  if(bit == 13) data-> bit_13 = value;
  if(bit == 14) data-> bit_14 = value;
  if(bit == 15) data-> bit_15 = value;
  if(bit == 16) data-> bit_16 = value;
  if(bit == 17) data-> bit_17 = value;
  if(bit == 18) data-> bit_18 = value;
  if(bit == 19) data-> bit_19 = value;
  if(bit == 20) data-> bit_20 = value;
  if(bit == 21) data-> bit_21 = value;
  if(bit == 22) data-> bit_22 = value;
  if(bit == 23) data-> bit_23 = value;
  if(bit == 24) data-> bit_24 = value;
  if(bit == 25) data-> bit_25 = value;
  if(bit == 26) data-> bit_26 = value;
  if(bit == 27) data-> bit_27 = value;
  if(bit == 28) data-> bit_28 = value;
  if(bit == 29) data-> bit_29 = value;
  if(bit == 30) data-> bit_30 = value;
  if(bit == 31) data-> bit_31 = value;
  if(bit == 32) data-> bit_32 = value;
  if(bit == 33) data-> bit_33 = value;
  if(bit == 34) data-> bit_34 = value;
  if(bit == 35) data-> bit_35 = value;
  if(bit == 36) data-> bit_36 = value;
  if(bit == 37) data-> bit_37 = value;
  if(bit == 38) data-> bit_38 = value;
  if(bit == 39) data-> bit_39 = value;
*/
}

void output_data(struct data *data,  uint8_t bit)
{

}
