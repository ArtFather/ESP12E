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

        #if BMP085_DEBUG == 1
        Serial.print("Number->");
        Serial.print(i);
        Serial.print("  Data->");
        Serial.println(BMP085_CALLDATA[i], DEC);
        #endif
    }
}

uint16_t BMP085_get_ut(void)
{
    uint16_t ut = 0;
    BMP085_write8(0xF4, 0x2E);
    delay(45);
    ut = BMP085_read16(0xF6);

#if BMP085_DEBUG == 1
    ut = 27898;
#endif

    return (ut);
}

uint32_t BMP085_get_up()
{
    uint32_t up = 0;

    BMP085_write8(0xF4, 0x34 + (OSS << 6));
    delay(14);

    up = BMP085_read16(0xF7);
    up <<= 8;
    up |= BMP085_read8(0xF4 + 2);
    up >>= (8 - OSS);

#if BMP085_DEBUG == 1
    up = 23843;
#endif

    return (up);
}

float BMP085_get_temp(void)
{
    float T = 0.00;
#if BMP085_DEBUG == 1
    int32_t X1 = (BMP085_get_ut() - (int32_t)BMP085_CALLDATADEF[5]) * ((int32_t)BMP085_CALLDATADEF[4]) >> 15;
    int32_t X2 = ((int32_t)BMP085_CALLDATADEF[9] << 11) / (X1 + (int32_t)BMP085_CALLDATADEF[10]);
    Serial.print("X1->");
    Serial.print(X1);
    Serial.print("  X2->");
    Serial.println(X2-1);
    int32_t B5 = X1 + X2;
#elif BMP085_DEBUG == 0
    int32_t X1 = (BMP085_get_ut() - (int32_t)BMP085_CALLDATA[5]) * ((int32_t)BMP085_CALLDATA[4]) >> 15;
    int32_t X2 = ((int32_t)BMP085_CALLDATA[9] << 11) / (X1 + (int32_t)BMP085_CALLDATA[10]);
    int32_t B5 = X1 + X2;
#endif
    T = (B5+8) >> 4;
    T /= 10;
    return (T);
}
