
#include "Sensor.h"

Sensor::Sensor(int pinOne, int pinTwo) {
    this.pinOne = pinOne;
    this.pinTwo = pinTwo;
}

string Sensor::stringifyData() {
    return "a^" + this.accelerometer.x + "_"
        + this.accelerometer.y + "_"
        + this.accelerometer.z + "a$"
        + "g^" + this.gyroscope.x + "_"
        + this.gyroscope.y + "_"
        + this.gyroscope.z + "g$";
}

void readAcceleration() {
    this.sensor.getAcceleration(
        &this.accelerometer.x,
        &this.accelerometer.y,
        &this.accelerometer.z
    );
}

void readRotation() {
    this.sensor.getRotation(
        &this.gyroscope.x,
        &this.gyroscope.y,
        &this.gyroscope.z
    );
}
