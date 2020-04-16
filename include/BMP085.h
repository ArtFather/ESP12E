#include <Arduino.h>
#include <Wire.h>

#define BMP085_SCL 4
#define BMP085_SDA 5
#define BMP085_ADDR 0x77

uint16_t BMP085_CALLREG[11] = {0xAA, 0xAC, 0xAE, 0xB0, 0xB2, 0xB4, 0xB6, 0xB8, 0xBA, 0xBC, 0xBE};
int16_t BMP085_CALLDATA[11];


uint16_t BMP085_read16(uint8_t reg);
void BMP085_get_cal_data(void);
uint8_t BMP085_read8(uint8_t reg);
uint16_t BMP085_get_ut(void);
uint16_t BMP085_get_up(void);
float BMP085_get_temp(void);
