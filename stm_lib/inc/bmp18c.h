#define PORT_BMP18C GPIOB
#define CLK_BMP18C GPIO_Pin_7
#define DATA_BMP18C GPIO_Pin_6


#define BMP18C_ADDRESS 0x77


#define AC1 0xAA
#define AC2 0xAC
#define AC3 0xAE
#define AC4 0xB0
#define AC5 0xB2
#define AC6 0xB4
#define VB1 0xB6
#define VB2 0xB8
#define MB 0xBA
#define MC 0xBC
#define MD 0xBE

struct data bmp18c;

void bmp18c_init(void);
