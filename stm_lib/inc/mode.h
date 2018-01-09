#include "delay_.h"
#include "stm32f10x_conf.h"

#ifdef STM32F103ZET6
#define MAX_CHANAL 48
#define NUMB_ADC 11
#endif

#ifdef STM32F103C8T6
#define MAX_CHANAL 18
#define NUMB_ADC 11
#endif

#define MAX_LEN_STR_LCD 16

volatile uint16_t CHANAL[MAX_CHANAL];
volatile GPIO_TypeDef *PORT_CHANAL[MAX_CHANAL];

uint16_t array_error[MAX_CHANAL][MAX_CHANAL];
uint16_t array_chek[MAX_CHANAL][MAX_CHANAL];
uint16_t adc_chek[MAX_CHANAL][MAX_CHANAL];
uint8_t counter_array_chek;
uint8_t counter_chanall;

uint8_t address_fragment;
uint8_t address_column;

GPIO_InitTypeDef GPIO_Config_port_in;
GPIO_InitTypeDef GPIO_Config_port_out;
GPIO_InitTypeDef GPIO_Config_port_mux;
ADC_InitTypeDef ADC_InitStructure;

char XW8_250_09_16[MAX_CHANAL][MAX_LEN_STR_LCD];

void adjust();
uint8_t options[16];
uint8_t number_repetitions_regime_open;
uint8_t matrix_for_validation;
uint8_t number_of_channels;
uint16_t adc_level_add;
uint8_t set_option_push;
uint8_t type_test_signal;
uint8_t mode_DDS;

void mode_jammers(double fraquent);
double fraquent_global;

void mode_broadbans(double broadbans);
double broadbans;

uint8_t mux_clobal;

void config_chanal_arm(void);
void data_collection(void);
void reset_array(void);

void mode_open(uint8_t);
void set_chek_chanall_mode_open(uint16_t chanall);
void chek_chanall_mode_open(uint16_t chanall);
void show_result_work_mode_open(void);
void reset_bit_in(void);
void set_bit_out(uint16_t chanall);
void reset_bit_out(uint16_t chanall);
uint16_t adc_calib(void);
uint16_t get_adc_value(void);
void mode_open_init(void);

void mode_analog(void);
void config_chanal_mode_analog(void);
uint16_t ADC_CH_control(uint16_t chanall, FunctionalState ADC_CH_STATE);
FunctionalState ADC_CH_STATE;

void mode_short(void);
uint8_t pin_null;
uint8_t numb_bits;
uint32_t address;
void show_result_work_mode_short(void);
void chek_adress_mode_short(uint8_t pin_null, uint8_t numb_bits);

void mode_matrix(void);
void show_result_work_mode_matrix(uint8_t switch_cap, char *state_switch);
void mode_matrix_init(void);
void matrix_09_16_XW8(void);
void arm_scanf(char *const_char, char *out_string);

void mode_combo(uint8_t);
uint8_t mode_combo_number;

void test_sys(void);

void mode_UART(void);
int counter_receive;
char USART3_buffer[1000];
enum Event { NO, YES } DATA_READ;

void config_chanal_mux(void);
void reset_chanal_mux(void);
void set_channal_mux(uint16_t chanall);

#ifdef STM32F103ZET6

#define PORT_MUX GPIOA
//#define PIN_MUX
// GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12

#define PORT_CONTROL_6MUX GPIOA
#define PIN_MUX6 GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3

#define CHANNEL_CONTROL_6MUX_0 GPIO_Pin_1
#define CHANNEL_CONTROL_6MUX_1 GPIO_Pin_2
#define CHANNEL_CONTROL_6MUX_2 GPIO_Pin_3

#define PORT_CONTROL_1MUX GPIOA
#define PIN_MUX1 GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6

#define CHANNEL_CONTROL_1MUX_0 GPIO_Pin_4
#define CHANNEL_CONTROL_1MUX_1 GPIO_Pin_5
#define CHANNEL_CONTROL_1MUX_2 GPIO_Pin_6

#define SET_MUX_PORT GPIOA
#define PIN_MUX_SET                                                            \
  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12

#define SET_MUX_0 GPIO_Pin_7
#define SET_MUX_1 GPIO_Pin_8
#define SET_MUX_2 GPIO_Pin_9
#define SET_MUX_3 GPIO_Pin_10
#define SET_MUX_4 GPIO_Pin_11
#define SET_MUX_5 GPIO_Pin_12

#define PORT_MUX GPIOA
#define PIN_MUX GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5

#define PORT_CONTROL_MUX GPIOA

#define MUX_CONTROL_0 GPIO_Pin_1
#define MUX_CONTROL_1 GPIO_Pin_2
#define ALL_CONTROLL_MUX GPIO_Pin_1 | GPIO_Pin_2

#define SET_MUX_CHANALL GPIOA

#define MUX_CHANAL_0 GPIO_Pin_3
#define MUX_CHANAL_1 GPIO_Pin_4
#define MUX_CHANAL_2 GPIO_Pin_5
#define ALL_CHANAL_MUX GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5

uint16_t ADC_CHANALL_PIN[NUMB_ADC];
uint8_t ADC_CHANALL[NUMB_ADC];
GPIO_TypeDef *PORT_ADC[MAX_CHANAL];

#endif

#ifdef STM32F103C8T6

#define PORT_MUX GPIOA
#define PIN_MUX GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5

#define PORT_CONTROL_MUX GPIOA

#define MUX_CONTROL_0 GPIO_Pin_1
#define MUX_CONTROL_1 GPIO_Pin_2
#define ALL_CONTROLL_MUX GPIO_Pin_1 | GPIO_Pin_2

#define SET_MUX_CHANALL GPIOA

#define MUX_CHANAL_0 GPIO_Pin_3
#define MUX_CHANAL_1 GPIO_Pin_4
#define MUX_CHANAL_2 GPIO_Pin_5
#define ALL_CHANAL_MUX GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5

uint16_t ADC_CHANALL_PIN[NUMB_ADC];
uint8_t ADC_CHANALL[NUMB_ADC];
GPIO_TypeDef *PORT_ADC[MAX_CHANAL];

#endif
