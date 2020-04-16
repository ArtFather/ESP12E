#include <Arduino.h>
#include "BMP085.cpp"

void setup() 
{
 Serial.begin(115200);
 Serial.println(" ");

 Wire.begin(BMP085_SCL, BMP085_SDA);
 //BMP085_get_cal_data();
 delay(50);
/*
 Serial.print("Raw temp->");
 Serial.print(BMP085_get_ut());
 Serial.print(" Raw pressure->");
 Serial.println(BMP085_get_up());
*/
 BMP085_get_cal_data();
 BMP085_get_ut();
 Serial.println(BMP085_get_temp());
}

 void loop()
 {

 }