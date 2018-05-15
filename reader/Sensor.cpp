#include "Sensor.h"

Sensor::Sensor(int pinOne, int pinTwo) {
  this->pinOne = pinOne;
  this->pinTwo = pinTwo;
}

String Sensor::serializeData() {
  return "{\"acc\":{\"x\":" + String(this->accelerometer.x) + ","
         + "\"y\":" + String(this->accelerometer.y) + ","
         + "\"z\":" + String(this->accelerometer.z) + "},"
         + "\"gyro\":{\"x\": " + String(this->gyroscope.x) + ","
         + "\"y\":" + String(this->gyroscope.y) + ","
         + "\"z\":" + String(this->gyroscope.z) + "}}";
}

void Sensor::readAcceleration() {
  int16_t ax, ay, az;
  this->sensor.getAcceleration(&ax, &ay, &az);

  this->accelerometer.x = ax;
  this->accelerometer.y = ay;
  this->accelerometer.z = az;
}

void Sensor::readRotation() {
  int16_t gx, gy, gz;
  this->sensor.getRotation(&gx, &gy, &gz);
  this->gyroscope.x = gx;
  this->gyroscope.y = gy;
  this->gyroscope.z = gz;
}

void Sensor::scaleRotation(int scale) {
  this->gyroscope.x /= scale;
  this->gyroscope.y /= scale;
  this->gyroscope.z /= scale;
}

void Sensor::scaleAcceleration(int scale) {
  this->accelerometer.x /= scale;
  this->accelerometer.y /= scale;
  this->accelerometer.z /= scale;
}

