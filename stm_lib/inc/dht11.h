
#define DHTPORT GPIOB
#define DHTPIN GPIO_Pin_0


//40-bit data
struct data
{
	uint8_t RH_data_integral;
	uint8_t RH_data_decimal;
	uint8_t T_data_integral;
	uint8_t T_data_decimal;
	uint8_t check_sum;
};

void dht_port_init(void);

void delay_dht(void);

void start_data_read(void);

void pack_data(void);

uint8_t data[40];
struct data dht_data;

