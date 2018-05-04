
#include "Wire.h"
#include "I2Cdev.h"
#include "Sensor.h"
#include "TimeStep.h"

#define SENSORS_COUNT 4
#define DEFAULT_DELAY 250
#define DEFAULT_BAUD_RATE 9600

Sensor holder[SENSORS_COUNT] = {
  Sensor(0, 0),
  Sensor(0, 1),
  Sensor(1, 0),
  Sensor(1, 1)
};

TimeStep* time;

void setup() {
  Wire.begin();
  Serial.begin(DEFAULT_BAUD_RATE);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  for (int i = 0; i < SENSORS_COUNT; i++) {
    digitalWrite(9, holder[i].pinOne);
    digitalWrite(10, holder[i].pinTwo);
    holder[i].sensor.initialize();
    // todo: calculate offsets
  }
  time = new TimeStep(millis());
}

void loop() {
  double timeStep = time->getCurrentStep(millis());
    
  String message = "";
  for (int i = 0; i < SENSORS_COUNT; i ++) {
    digitalWrite(9, holder[i].pinOne);
    digitalWrite(10, holder[i].pinTwo);
    
    if (!holder[i].sensor.testConnection()) {
      continue;
    }
    holder[i].sensor.initialize();
    
    holder[i].readAcceleration();
    holder[i].readRotation();
    holder[i].scaleRotation(131);
    holder[i].calculateAngles(timeStep);
    if (message.length() == 0) {
          message += "{\"id\":" + String(i+1) + ",\"data\":" + holder[i].serializeData() + "}";
    } else {
          message += ",{\"id\":" + String(i+1) + ",\"data\":" + holder[i].serializeData() + "}";
    }
  }

  time->tick();
  Serial.println("[" + message + "]");
  delay(DEFAULT_DELAY / 2);
  Serial.println("$");
  delay(DEFAULT_DELAY / 2);
}
