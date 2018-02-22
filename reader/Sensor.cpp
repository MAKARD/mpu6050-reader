
#include "Sensor.h"

Sensor::Sensor(int pinOne, int pinTwo) {
    this->pinOne = pinOne;
    this->pinTwo = pinTwo;
}

String Sensor::serializeData(void) {
  return "{'acc':{'x':" + String(this->accelerometer.x) + ","
          + "'y':" + String(this->accelerometer.y) + ","
          + "'z':" + String(this->accelerometer.z) + "},"
          + "'gyro':{'x': " + String(this->gyroscope.x) + ","
          + "'y':" + String(this->gyroscope.y) + ","
          + "'z':" + String(this->gyroscope.z) + "}}";
}

void Sensor::readAcceleration(void) {
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
