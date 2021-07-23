#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>

#include "WebServer.h"
#include "MPU6050.h"

// global variables
WebServer *web_server;
MPU6050 *mpu_6050;
int16_t accel_reading[3];
char json_buffer[30];

void setup() {
    Serial.begin (115200);
    web_server = new WebServer(80);
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

    // convert readings to json string
    StaticJsonDocument<48> doc;
    copyArray(accel_reading, doc.to<JsonArray>());
    serializeJson(doc, json_buffer);

    // send the event to the browser
    web_server->send_event("accel_readings", json_buffer);

    delay (200);
}
