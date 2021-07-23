#include <Arduino.h>
#include <Wire.h>

#include "MPU6050.h"

// global variables
MPU6050 *mpu_6050;
int16_t accel_reading[3];

void setup() {
    Serial.begin (115200);
    mpu_6050 = new MPU6050(0x68);
}

void loop()
{
    // get the accelerator readings and print them to the serial monitor
    mpu_6050->get_accel_reading(accel_reading);
    Serial.print("Accelerometer: ");
    Serial.print(accel_reading[0]); Serial.print(" | ");
    Serial.print(accel_reading[1]); Serial.print(" | ");
    Serial.println(accel_reading[2]);

    delay (200);
}
