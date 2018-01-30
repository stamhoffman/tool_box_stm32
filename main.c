#include <stm32f10x_conf.h>

RCC_ClocksTypeDef RCC_value;
ErrorStatus HSE_ON;
FlagStatus PLL_ON;
uint8_t source_clk;

struct data dht11_data;
struct data send;

int main(void) {

  RCC_Config();
  GPIO_Config();

  LCD_init();
  LCD_print("Tool_Box_STM32", 0, 0);
  lcd_out_number(RCC_value.HCLK_Frequency, 0, 1);
  LCD_print("Hz", 50, 1);


#ifdef CLIENT
  dht11_data.number_of_world = 5;
  dht11_data.bit_order = 8;
#endif

#ifdef SERVER
  send.number_of_world = 5;
  send.bit_order = 8;

  send.world_1 = 20;
  send.world_2 = 20;
  send.world_3 = 20;
  send.world_4 = 20;

  unpack_world(&send);
#endif

#ifdef DEBUG


#endif


while (1) {

#ifdef CLIENT
	  dht11();
	  LCD_clrScr();
	  LCD_print("DHT11 sensor", 0, 0);
	  LCD_print("H = ", 0, 2);
	  lcd_out_number(dht11_data.world_1, 20, 2);
	  LCD_print("%", 38, 2);
	  LCD_print("T = ", 0, 3);
	  lcd_out_number(dht11_data.world_3, 20, 3);
	  LCD_print("C", 38, 3);
	  LCD_print("CRC = ", 0, 5);
	  LCD_print(calc_crc(&dht11_data), 25, 5);
	  delay_sec(1);
#endif


#ifdef DEBUG

	uint8_t data;
	bmp18c_init(I2C1, 100000, GPIOB, GPIO_Pin_6, GPIO_Pin_7);
	delay_ms(20);
	start_bmp18c_rw(I2C1, read_data_bmp, BMP18C_ADDRESS);
	I2C_WriteData(I2C1, AC1);

   while(1)
   {

		data = I2C_ReadData(I2C1);
		LCD_clrScr();
		LCD_print("data", 0, 0);
		lcd_out_number(data, 0, 1);
   }

#endif

#ifdef SERVER
   while (((DHTPORT->IDR) & (DHTPIN)));
   send_onewire();
#endif
  }
}

void GPIO_Config(void) {

#ifdef CLIENT
  onewire_port_init(DHTPORT, DHTPIN);
#endif

#ifdef SERVER
  onewire_port_init(DHTPORT, DHTPIN);
#endif

#ifdef DEBUG
  onewire_port_init(DHTPORT,DHTPIN);
#endif

  GPIO_InitTypeDef LCD_PORT;
  LCD_PORT.GPIO_Pin = GPIO_Pin_All;
  LCD_PORT.GPIO_Mode = GPIO_Mode_Out_PP;
  LCD_PORT.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &LCD_PORT);

  LCD_setRST(GPIOA, GPIO_Pin_0);
  LCD_setCE(GPIOA, GPIO_Pin_1);
  LCD_setDC(GPIOA, GPIO_Pin_2);
  LCD_setDIN(GPIOA, GPIO_Pin_3);
  LCD_setCLK(GPIOA, GPIO_Pin_4);

  GPIO_InitTypeDef CLK_PIN;

  CLK_PIN.GPIO_Mode = GPIO_Mode_Out_PP;
  CLK_PIN.GPIO_Pin = GPIO_Pin_5;
  CLK_PIN.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &CLK_PIN);
}

void RCC_Config(void) {

#ifdef QUARZ
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);

  if ((HSE_ON = RCC_WaitForHSEStartUp()) == SUCCESS) {
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div16);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08)
      ;

    RCC_ClockSecuritySystemCmd(ENABLE);
  }
#endif

  RCC_GetClocksFreq(&RCC_value);
  SysTick_Config(RCC_value.HCLK_Frequency / 1000);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}

void dht11(void) {
  start_data_read(DHTPORT, DHTPIN);
  received_data(DHTPORT, DHTPIN, &dht11_data);
  pack_world(&dht11_data);
}

void send_onewire(void)
{
	start_data_send(DHTPORT, DHTPIN);
	transend_data(DHTPORT, DHTPIN,&send);
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line) {
   LCD_clrScr();
   lcd_out_number(*(uint32_t *)file, 0, 0);
   lcd_out_number(line, 0, 1);
 }
#endif

///*
// #include "stm32f10x.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_usart.h"
//#include "stm32f10x_dma.h"
//#include "stm32f10x_tim.h"
//#include "stm32f10x_i2c.h"
//#include "misc.h"
//#include "stdio.h"
//#include "string.h"
//
//#include "bmp280.h"
//
//volatile unsigned char FLAG_USART;
//
//void I2C1_init(void)
//{
//    I2C_InitTypeDef  I2C_InitStructure;
//    GPIO_InitTypeDef  GPIO_InitStructure;
//
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//
//    /* Configure I2C_EE pins: SCL and SDA */
//    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//    /* I2C configuration */
//    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
//    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
//    I2C_InitStructure.I2C_OwnAddress1 = 0x38;
//    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
//    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//    I2C_InitStructure.I2C_ClockSpeed = 100000;
//
//    /* I2C Peripheral Enable */
//    I2C_Cmd(I2C1, ENABLE);
//    /* Apply I2C configuration after enabling it */
//    I2C_Init(I2C1, &I2C_InitStructure);
//}
//
//
///*******************************************************************/
//
///*******************************************************************/
//// UART DMA
///*******************************************************************/
//char usart_buffer[80] = {'\0'};
///*******************************************************************/
//void usart_dma_init(void)
//{
//	/* Enable USART1 and GPIOA clock */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//	/* DMA */
//	DMA_InitTypeDef DMA_InitStruct;
//	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
//	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&usart_buffer[0];
//	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
//	DMA_InitStruct.DMA_BufferSize = sizeof(usart_buffer);
//	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
//	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
//	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel4, &DMA_InitStruct);
//
//	/* NVIC Configuration */
//	NVIC_InitTypeDef NVIC_InitStructure;
//	/* Enable the USARTx Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	/* Configure the GPIOs */
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	/* Configure USART1 Rx (PA.10) as input floating */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	/* Configure the USART1 */
//	USART_InitTypeDef USART_InitStructure;
//
//	/* USART1 configuration ------------------------------------------------------*/
//	/* USART1 configured as follow:
//		- BaudRate = 115200 baud
//		- Word Length = 8 Bits
//		- One Stop Bit
//		- No parity
//		- Hardware flow control disabled (RTS and CTS signals)
//		- Receive and transmit enabled
//		- USART Clock disabled
//		- USART CPOL: Clock is active low
//		- USART CPHA: Data is captured on the middle
//		- USART LastBit: The clock pulse of the last data bit is not output to
//			the SCLK pin
//	 */
//	USART_InitStructure.USART_BaudRate = 9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	//USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_InitStructure.USART_Mode = USART_Mode_Tx;
//
//	USART_Init(USART1, &USART_InitStructure);
//
//	/* Enable USART1 */
//	USART_Cmd(USART1, ENABLE);
//
//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
//	//DMA_Cmd(DMA1_Channel4, ENABLE);
//
//	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
//	NVIC_EnableIRQ(DMA1_Channel4_IRQn);
//}
//
///*******************************************************************/
//void USARTSendDMA(char *pucBuffer)
//{
//	strcpy(usart_buffer, pucBuffer);
//
//	/* Restart DMA Channel*/
//	DMA_Cmd(DMA1_Channel4, DISABLE);
//	DMA1_Channel4->CNDTR = strlen(pucBuffer);
//	DMA_Cmd(DMA1_Channel4, ENABLE);
//}
//
///*******************************************************************/
//void DMA1_Channel4_IRQHandler(void)
//{
//	DMA_ClearITPendingBit(DMA1_IT_TC4);
//	DMA_Cmd(DMA1_Channel4, DISABLE);
//}
///*******************************************************************/
//
///*******************************************************************/
//// TIM4
///*******************************************************************/
//void TIM4_init(void) {
//	// TIMER4
//    TIM_TimeBaseInitTypeDef TIMER_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//
//  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//
//  	TIM_TimeBaseStructInit(&TIMER_InitStructure);
//    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIMER_InitStructure.TIM_Prescaler = 8000;
//    TIMER_InitStructure.TIM_Period = 10000;
//    TIM_TimeBaseInit(TIM4, &TIMER_InitStructure);
//    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
//    TIM_Cmd(TIM4, ENABLE);
//
//    /* NVIC Configuration */
//    /* Enable the TIM4_IRQn Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//}
//
///*******************************************************************/
//void TIM4_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
//	{
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//
//		FLAG_USART = 1;
//	}
//}
///*******************************************************************/
//
//int main(void)
//{
//	char buffer[80] = {'\0'};
//
//	long temperature = 0;
//	long pressure = 0;
//
//	I2C1_init();
//	BMP280_Init();
//	usart_dma_init();
//
//	TIM4_init();
//
//    while(1)
//    {
//		if (FLAG_USART == 1) {
//			bmp280Convert(&temperature, &pressure);
//			sprintf(buffer, "Temperature: %d, Pressure: %d\r\n", (int)temperature/10, (int)pressure);
//    		USARTSendDMA(buffer);
//			FLAG_USART = 0;
//    	}
//    }
//}
// *
// *
// *
// */
//
