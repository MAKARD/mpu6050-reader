
#include "Wire.h"
#include "I2Cdev.h"
#include "Sensor.h"

#define SENSORS_COUNT 4
#define DEFAULT_DELAY 250
#define DEFAULT_BAUD_RATE 9600

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
        digitalWrite(9, holder[i].pinOne);
        digitalWrite(10, holder[i].pinTwo);
        holder[i].sensor.initialize();
        holder[i].initialized = holder[i].sensor.testConnection();
        // todo: calculate offsets
    }
}

void loop() {
    Serial.println("[");
    int activeSensors = SENSORS_COUNT;
    for (int i = 0; i < SENSORS_COUNT; i ++) {
        if (!holder[i].initialized){
          activeSensors--;
          continue;
        }
        digitalWrite(9, holder[i].pinOne);
        digitalWrite(10, holder[i].pinTwo);

        holder[i].readAcceleration();
        holder[i].readRotation();
        Serial.println("{\"id\":" + String(i) + ",\"data\":" + holder[i].serializeData() + "}" + (i == activeSensors ? "" : ","));
    }
    Serial.println("]");
    delay(DEFAULT_DELAY / 2);
    Serial.println("$");
    delay(DEFAULT_DELAY / 2);
}
