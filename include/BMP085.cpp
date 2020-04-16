#include "BMP085.h"

uint8_t BMP085_read8(uint8_t reg)
{
    uint16_t data = 0;
    Wire.beginTransmission(BMP085_ADDR);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(BMP085_ADDR, 1);
    data = Wire.read(); // receive DATA
    Wire.endTransmission();

    return (data);
}

uint16_t BMP085_read16(uint8_t reg)
{
    uint16_t data;
    Wire.beginTransmission(BMP085_ADDR);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(BMP085_ADDR, 2);
    data = Wire.read();
    data <<= 8;
    data |= Wire.read();
    Wire.endTransmission();

    return (data);
}

void BMP085_write8(uint8_t reg, uint8_t dat)
{
    Wire.beginTransmission(BMP085_ADDR);
    Wire.write(reg);
    Wire.write(dat);
    Wire.endTransmission();
}

void BMP085_get_cal_data(void)
{
    for (int i = 0; i < 11; i++)
    {
        BMP085_CALLDATA[i] = BMP085_read16(BMP085_CALLREG[i]);
        Serial.print("Number->");
        Serial.print(i);
        Serial.print("  Data->");
        Serial.println(BMP085_CALLDATA[i], DEC);
    }
}

uint16_t BMP085_get_ut(void)
{
    uint16_t ut = 0;
    BMP085_write8(0xF4, 0x2E);
    delay(45);
    ut = BMP085_read16(0xF6);
    return (ut);
}

uint16_t BMP085_get_up()
{
    uint16_t up = 0;
    BMP085_write8(0xF4, 0x34 + (3 << 6));
    delay(14);
    up = BMP085_read16(0xF7);
    return (up);
}

