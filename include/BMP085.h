#include <Arduino.h>
#include <Wire.h>

#define BMP085_SCL 4
#define BMP085_SDA 5
#define BMP085_ADDR 0x77
#define OSS 3
#define BMP085_DEBUG 0

uint16_t BMP085_CALLREG[11] = {0xAA, 0xAC, 0xAE, 0xB0, 0xB2, 0xB4, 0xB6, 0xB8, 0xBA, 0xBC, 0xBE};
int16_t BMP085_CALLDATADEF[11] = {408, -72, -14383, 32741, 32757, 23153, 6190, 4, -32768, -8711, 2868};
int16_t BMP085_CALLDATA[11];


uint16_t BMP085_read16(uint8_t reg);
void BMP085_get_cal_data(void);
uint8_t BMP085_read8(uint8_t reg);
uint16_t BMP085_get_ut(void);
uint32_t BMP085_get_up(void);
float BMP085_get_temp(void);
int BMP085_get_pressure(void);
