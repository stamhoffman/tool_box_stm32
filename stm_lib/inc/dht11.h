
#define DHTPORT GPIOC
#define DHTPIN GPIO_Pin_15



//40-bit data
struct data
{
	int bit40[40];
	int RH_data_integral;
	int RH_data_decimal;
	int T_data_integral;
	int T_data_decimal;
	int check_sum;
};




void dht_port_init(void);

void delay_dht(void);

void start_data_read(void);

void pack_data(void);

int data[40];
struct data dht_data;
