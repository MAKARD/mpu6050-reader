
#include "Wire.h"
#include "I2Cdev.h"
#include "Sensor.h"
#include "StandardCplusplus"

#define SENSORS_COUNT = 4
#define DEFAULT_DELAY = 250
#define DEFAULT_BAUD_RATE = 9600

Sensor holder[SENSORS_COUNT] = {
    Sensor(0, 0),
    Sensor(0, 1),
    Sensor(1, 0),
    Sensor(1, 1)
};

void setup() {
    Wire.begin();
    Serial.begin(DEFAULT_BAUD_RATE);

    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    for (int i = 0; i < SENSORS_COUNT; i++) {
        string sensorName = i + "(" + holder[i].pinOne + holder[i].pinTwo + ")");
        Serial.println("Initializing sensor " + sensorName;

        digitalWrite(9, holder[i].pinOne);
        digitalWrite(10, holder[i].pinTwo);

        holder[i].sensor.initialize();
        Serial.println("Testing device connections...");
        Serial.println(holder[i].sensor.testConnection()
            ? "Sensor" + sensorName + "connection successful" 
            : "Sensor" + sensorName + "connection failed");

        // todo: calculate offsets
    }
}

void loop() {
    for (int i = 0; i < SENSORS_COUNT; i ++) {
        digitalWrite(9, holder[i].pinOne);
        digitalWrite(10, holder[i].pinTwo);

        holder[i].readAcceleration();
        holder[i].readRotation();
        
        Serial.println(holder[i].stringifyData());
        delay(250);
    }
}
