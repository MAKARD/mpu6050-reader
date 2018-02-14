
#include "Sensor.h"

Sensor::Sensor(int pinOne, int pinTwo) {
    this.pinOne = pinOne;
    this.pinTwo = pinTwo;
}

string Sensor::stringifyData() {
    return "a^" + this.sensor.accelerometer.x + "_"
        + this.sensor.accelerometer.y + "_"
        + this.sensor.accelerometer.z + "a$"
        + "g^" + this.sensor.gyroscope.x + "_"
        + this.sensor.gyroscope.y + "_"
        + this.sensor.gyroscope.z + "g$";
}

void readAcceleration() {
    this.sensor.getAcceleration(
        &this.sensor.accelerometer.x,
        &this.sensor.accelerometer.y,
        &this.sensor.accelerometer.z
    );
}

void readRotation() {
    this.sensor.getRotation(
        &this.sensor.gyroscope.x,
        &this.sensor.gyroscope.y,
        &this.sensor.gyroscope.z
    );
}
