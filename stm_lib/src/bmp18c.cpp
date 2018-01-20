#include <stm32f10x_conf.h>


void bmp18c_init(void)
{
	GPIO_InitTypeDef GPIO_BMP18C;
	GPIO_BMP18C.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_BMP18C.GPIO_Pin = CLK_BMP18C | DATA_BMP18C;
	GPIO_BMP18C.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_BMP18C, &GPIO_BMP18C);

	I2C_InitTypeDef BMP18C;
	BMP18C.I2C_Ack = I2C_Ack_Enable;
	BMP18C.I2C_ClockSpeed = 200000;
	BMP18C.I2C_Mode = I2C_Mode_SMBusHost;
	BMP18C.I2C_OwnAddress1 = BMP18C_ADDRESS;
	BMP18C.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	BMP18C.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_Init(I2C1, &BMP18C);
}
