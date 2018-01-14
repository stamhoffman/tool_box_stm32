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

void unpack_world(struct data *data)
{
	int crc;

	if (data-> number_of_world >= 1)
	   memcpy(&data->world_1 + 1, &data->world_1, sizeof(char));
	if (data -> number_of_world >= 2)
	   memcpy(&data->world_2 + 1, &data->world_2, sizeof(char));
	if (data -> number_of_world >= 3)
	   memcpy(&data->world_3 + 1, &data->world_3, sizeof(char));
	if (data -> number_of_world >= 4)
	   memcpy(&data->world_4 + 1, &data->world_4, sizeof(char));

	if (data-> number_of_world == 3) crc = (data-> world_1 & data-> world_2);
	if (data-> number_of_world == 4) crc = (data-> world_1 & data-> world_2 & data-> world_3);
	if (data-> number_of_world == 5) crc = (data-> world_1 & data-> world_2 & data-> world_3 & data-> world_4);

	if (data -> number_of_world >= 5)
	   memcpy(&data->world_5 + 1, &crc, sizeof(char));
}


char *calc_crc(struct data *data) {
  int crc;

  if (data-> number_of_world == 3) crc = (data-> world_1 & data-> world_2);
  if (data-> number_of_world == 4) crc = (data-> world_1 & data-> world_2 & data-> world_3);
  if (data-> number_of_world == 5) crc = (data-> world_1 & data-> world_2 & data-> world_3 & data-> world_4);

  if ((data-> world_5) == crc) return "OK";
  	  else return "ERROR";
}

void push_bit(struct data *data, uint8_t bit, int value)
{
  if(bit == 0) data-> bit_7 = value;//0
  if(bit == 1) data-> bit_6 = value;//1
  if(bit == 2) data-> bit_5 = value;//2
  if(bit == 3) data-> bit_4 = value;//3
  if(bit == 4) data-> bit_3 = value;//4
  if(bit == 5) data-> bit_2 = value;//5
  if(bit == 6) data-> bit_1 = value;//6
  if(bit == 7) data-> bit_0 = value;//7

  if(bit == 8) data-> bit_15 = value;//0
  if(bit == 9) data-> bit_14 = value;//1
  if(bit == 10) data-> bit_13 = value;//2
  if(bit == 11) data-> bit_12 = value;//3
  if(bit == 12) data-> bit_11 = value;//4
  if(bit == 13) data-> bit_10 = value;//5
  if(bit == 14) data-> bit_9 = value;//6
  if(bit == 15) data-> bit_8 = value;//7

  if(bit == 16) data-> bit_23 = value;//0
  if(bit == 17) data-> bit_22 = value;//1
  if(bit == 18) data-> bit_21 = value;//2
  if(bit == 19) data-> bit_20 = value;//3
  if(bit == 20) data-> bit_19 = value;//4
  if(bit == 21) data-> bit_18 = value;//5
  if(bit == 22) data-> bit_17 = value;//6
  if(bit == 23) data-> bit_16 = value;//7

  if(bit == 24) data-> bit_31 = value;//0
  if(bit == 25) data-> bit_30 = value;//1
  if(bit == 26) data-> bit_29 = value;//2
  if(bit == 27) data-> bit_28 = value;//3
  if(bit == 28) data-> bit_27 = value;//4
  if(bit == 29) data-> bit_26 = value;//5
  if(bit == 30) data-> bit_25 = value;//6
  if(bit == 31) data-> bit_24 = value;//7

  if(bit == 32) data-> bit_39 = value;//0
  if(bit == 33) data-> bit_38 = value;//1
  if(bit == 34) data-> bit_37 = value;//2
  if(bit == 35) data-> bit_36 = value;//3
  if(bit == 36) data-> bit_35 = value;//4
  if(bit == 37) data-> bit_34 = value;//5
  if(bit == 38) data-> bit_33 = value;//6
  if(bit == 39) data-> bit_32 = value;//7
}

int pop_bit(struct data *data,  uint8_t bit)
{
  if(bit == 0) return data-> bit_7;//0
  if(bit == 1) return data-> bit_6;//1
  if(bit == 2) return data-> bit_5;//2
  if(bit == 3) return data-> bit_4;//3
  if(bit == 4) return data-> bit_3;//4
  if(bit == 5) return data-> bit_2;//5
  if(bit == 6) return data-> bit_1;//6
  if(bit == 7) return data-> bit_0;//7

  if(bit == 8) return data-> bit_15;//0
  if(bit == 9) return data-> bit_14;//1
  if(bit == 10) return data-> bit_13;//2
  if(bit == 11) return data-> bit_12;//3
  if(bit == 12) return data-> bit_11;//4
  if(bit == 13) return data-> bit_10;//5
  if(bit == 14) return data-> bit_9;//6
  if(bit == 15) return data-> bit_8;//7

  if(bit == 16) return data-> bit_23;//0
  if(bit == 17) return data-> bit_22;//1
  if(bit == 18) return data-> bit_21;//2
  if(bit == 19) return data-> bit_20;//3
  if(bit == 20) return data-> bit_19;//4
  if(bit == 21) return data-> bit_18;//5
  if(bit == 22) return data-> bit_17;//6
  if(bit == 23) return data-> bit_16;//7

  if(bit == 24) return data-> bit_31;//0
  if(bit == 25) return data-> bit_30;//1
  if(bit == 26) return data-> bit_29;//2
  if(bit == 27) return data-> bit_28;//3
  if(bit == 28) return data-> bit_27;//4
  if(bit == 29) return data-> bit_26;//5
  if(bit == 30) return data-> bit_25;//6
  if(bit == 31) return data-> bit_24;//7

  if(bit == 32) return data-> bit_39;//0
  if(bit == 33) return data-> bit_38;//1
  if(bit == 34) return data-> bit_37;//2
  if(bit == 35) return data-> bit_36;//3
  if(bit == 36) return data-> bit_35;//4
  if(bit == 37) return data-> bit_34;//5
  if(bit == 38) return data-> bit_33;//6
  if(bit == 39) return data-> bit_32;//7

  return 0;
}












