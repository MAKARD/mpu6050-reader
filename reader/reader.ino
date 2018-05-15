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
  }

  time = new TimeStep();
}

void loop() {
  double timeStep = time->getCurrentStep();

  String message = "";
  for (int i = 0; i < SENSORS_COUNT; i ++) {
    digitalWrite(9, holder[i].pinOne);
    digitalWrite(10, holder[i].pinTwo);

    if (!holder[i].sensor.testConnection()) {
      continue;
    }
    
    holder[i].readRotation();
    holder[i].readAcceleration();
    holder[i].scaleRotation(131);
    holder[i].scaleAcceleration(16384);

    String messageBody = "{\"id\":\"" + String(holder[i].pinOne) + String(holder[i].pinTwo) + "\", \"time\":" + String(timeStep) + ",\"data\":" + holder[i].serializeData() + "}";
    if (message.length() != 0) {
      message += "," + messageBody;
    } else {
      message += messageBody;
    }

  }

  Serial.println("[" + message + "]");
  delay(DEFAULT_DELAY / 2);
  Serial.println("$");
  delay(DEFAULT_DELAY / 2);
}
