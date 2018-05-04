#include "Sensor.h"

const double Pi = 3.141592;

Sensor::Sensor(int pinOne, int pinTwo) {
  this->pinOne = pinOne;
  this->pinTwo = pinTwo;

  this->gyroAngles.x = 0;
  this->gyroAngles.y = 0;
  this->gyroAngles.z = 0;
}

String Sensor::serializeRawData() {
  return "{\"acc\":{\"x\":" + String(this->accelerometer.x) + ","
         + "\"y\":" + String(this->accelerometer.y) + ","
         + "\"z\":" + String(this->accelerometer.z) + "},"
         + "\"gyro\":{\"x\": " + String(this->gyroscope.x) + ","
         + "\"y\":" + String(this->gyroscope.y) + ","
         + "\"z\":" + String(this->gyroscope.z) + "}}";
}

String Sensor::serializeAnglesData() {
  return "{\"x\":" + String(this->angles.x) + ","
         + "\"y\":" + String(this->angles.y) + ","
         + "\"z\":" + String(this->angles.z) + "}";
}

void Sensor::readAcceleration() {
  this->sensor.getAcceleration(
    &this->accelerometer.x,
    &this->accelerometer.y,
    &this->accelerometer.z
  );
}

void Sensor::readRotation() {
  this->sensor.getRotation(
    &this->gyroscope.x,
    &this->gyroscope.y,
    &this->gyroscope.z
  );
}

void Sensor::scaleRotation(int16_t scale) {
  this->gyroscope.x /= scale;
  this->gyroscope.y /= scale;
  this->gyroscope.z /= scale;
}

void Sensor::calculateAngles(double timeStep) {
  double arx = (180 / Pi) * atan(this->accelerometer.x / sqrt(square(this->accelerometer.y) + square(this->accelerometer.z)));
  double ary = (180 / Pi) * atan(this->accelerometer.y / sqrt(square(this->accelerometer.x) + square(this->accelerometer.z)));
  double arz = (180 / Pi) * atan(sqrt(square(this->accelerometer.y) + square(this->accelerometer.z)) / 2);

  if (!this->gyroAngles.x && !this->gyroAngles.y && !this->gyroAngles.z) {
    this->gyroAngles.x = arx;
    this->gyroAngles.y = ary;
    this->gyroAngles.z = arz;
  } else {
    this->gyroAngles.x += (timeStep * this->gyroscope.x);
    this->gyroAngles.y += (timeStep * this->gyroscope.y);
    this->gyroAngles.z += (timeStep * this->gyroscope.z);
  }

  this->angles.x = (0.1 * arx) + (0.9 * this->gyroAngles.x);
  this->angles.y = (0.1 * ary) + (0.9 * this->gyroAngles.y);
  this->angles.z = (0.1 * arz) + (0.9 * this->gyroAngles.z);
}

