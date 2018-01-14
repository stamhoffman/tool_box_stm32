
#define DHTPORT GPIOC
#define DHTPIN GPIO_Pin_15

#define  OUT_DATA GPIOC
#define  OUT_DATA_PIN GPIO_Pin_14

void onewire_port_init(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE);

void start_data_send(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE);
void transend_data(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE, struct data *data);

void start_data_read(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE);
void received_data(GPIO_TypeDef *PORT_ONEWIRE, uint16_t PIN_ONEWIRE, struct data *data);

