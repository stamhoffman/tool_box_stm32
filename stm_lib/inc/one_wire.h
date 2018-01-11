
#define DHTPORT GPIOC
#define DHTPIN GPIO_Pin_15

void onewire_port_init(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE);
void received_data(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE, struct data *data);
void transend_data(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE, struct data *data);
void start_data_read(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE);
