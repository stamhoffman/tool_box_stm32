#include <stm32f10x_conf.h>


void pack_world(struct data *data, uint8_t number_of_world)
{
  assert(number_of_world < 6);
  if(number_of_world >= 1) memcpy(&data.world_1, &data.world_1 + 1, sizeof(uint8_t));
  if(number_of_world >= 2) memcpy(&data.world_2, &data.world_2 + 1, sizeof(uint8_t));
  if(number_of_world >= 3) memcpy(&data.world_3, &data.world_3 + 1, sizeof(uint8_t));
  if(number_of_world >= 4) memcpy(&data.world_4, &data.world_4 + 1, sizeof(uint8_t));
  if(number_of_world >= 5) memcpy(&data.world_5, &data.world_5 + 1, sizeof(uint8_t));
}

void calc_crc_world(struct data *data, uint8_t number_of_world)
{
  if(number_of_world >= 1);
  if(number_of_world >= 2);
  if(number_of_world >= 3) data.world_3 = (data.world_1 | data.world_2);
  if(number_of_world >= 4) data.world_4 = (data.world_1 | data.world_2 | data.world_3);
  if(number_of_world >= 5) data.world_5 = (data.world_1 | data.world_2 |data.world_3 | data.world_4);
}

void input_data(struct data *data, uint8_t number_of_world, uint8_t bit_order)
{

}
