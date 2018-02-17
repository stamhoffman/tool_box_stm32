#define BMP18C_ADDRESS 0xEE

#define read_data_bmp ((uint8_t)0x01)
#define write_data_bmp ((uint8_t)0x00)

#define AC1 0xAA
#define AC1_ 0xAB

#define AC2 0xAC
#define AC2_ 0xAD

#define AC3 0xAE
#define AC3_ 0xAF

#define AC4 0xB0
#define AC4_ 0xB1

#define AC5 0xB2
#define AC5_ 0xB3

#define AC6 0xB4
#define AC6_ 0xB5

#define VB1 0xB6
#define VB1_ 0xB7

#define VB2 0xB8
#define VB2_ 0xB9

#define MB 0xBA
#define MB_ 0xBB

#define MC 0xBC
#define MC_ 0xBD

#define MD 0xBE
#define MD_ 0xBF


#define TEMP 0xF6
#define TEMP_ 0xF7

#define TEMP_CR 0xF4
#define TEMP_CR_VAL 0x2E

#define PRESCURE_CR 0xF4
#define PRESCURE_CR_VAL 0x34

#define PRESCURE 0xF6
#define PRESCURE_ 0xF7
#define PRESCURE_A 0xF8


struct data bmp18c;

void bmp18c_init(I2C_TypeDef* I2Cx, uint32_t speed, GPIO_TypeDef* GPIOx, uint16_t CLK_BMP18C,  uint16_t DATA_BMP18C);

int I2C_WriteData(I2C_TypeDef* I2Cx,  uint8_t slaveAddress, uint8_t registr, uint8_t transend_data);

uint8_t I2C_ReadData(I2C_TypeDef* I2Cx, uint8_t slaveAddress,  uint8_t registr, uint8_t *received_data, uint8_t size_data_byte);

void read_bar();




































/*
 *
 *
 * #ifndef _BMP280_LIB_H_
#define _BMP280_LIB_H_

#define BMP280_addr 0xED

#define	BMP280_REG_CONTROL 0xF4
#define	BMP280_REG_CONFIG 0xF5

#define	BMP280_REG_RESULT_PRESSURE 0xF7			// 0xF7(msb) , 0xF8(lsb) , 0xF9(xlsb) : stores the pressure data.
#define BMP280_REG_RESULT_TEMPRERATURE 0xFA		// 0xFA(msb) , 0xFB(lsb) , 0xFC(xlsb) : stores the temperature data.

#define	BMP280_OVERSAMPLING_T1		0x20
#define	BMP280_OVERSAMPLING_T2		0x40
#define	BMP280_OVERSAMPLING_T4		0x60
#define	BMP280_OVERSAMPLING_T8		0x80
#define	BMP280_OVERSAMPLING_T16		0xA0

#define	BMP280_OVERSAMPLING_P1		0x04
#define	BMP280_OVERSAMPLING_P2		0x08
#define	BMP280_OVERSAMPLING_P4		0x0C
#define	BMP280_OVERSAMPLING_P8		0x10
#define	BMP280_OVERSAMPLING_P16		0x14

#define	BMP280_MODE_SLEEP			0x00
#define	BMP280_MODE_FORCED			0x01
#define	BMP280_MODE_NORMAL			0x03

#define	BMP280_TSB_0_5				0x00
#define	BMP280_TSB_62_5				0x20
#define	BMP280_TSB_125				0x40
#define	BMP280_TSB_250				0x60
#define	BMP280_TSB_500				0x80
#define	BMP280_TSB_1000				0xA0
#define	BMP280_TSB_2000				0xC0
#define	BMP280_TSB_4000				0xE0

#define	BMP280_FILTER_OFF			0x00
#define	BMP280_FILTER_COEFFICIENT2	0x04
#define	BMP280_FILTER_COEFFICIENT4	0x08
#define	BMP280_FILTER_COEFFICIENT8	0x0C
#define	BMP280_FILTER_COEFFICIENT16	0x10

#define	BMP280_SPI_OFF	0x00
#define	BMP280_SPI_ON	0x01

#define	BMP280_MEAS			(BMP280_OVERSAMPLING_T16 | BMP280_OVERSAMPLING_P16 | BMP280_MODE_NORMAL)
#define	BMP280_CONFIG		(BMP280_TSB_0_5 | BMP280_FILTER_COEFFICIENT16 | BMP280_SPI_OFF)

void BMP280_Init(void);
void bmp280Convert(long* temperature, long* pressure);
long bmp280CalcAltitude(long pressure);

#endif
 *
 *
 *
 *
 */
