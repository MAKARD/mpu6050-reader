#include "Arduino.h"
#include "TimeStep.h"

TimeStep::TimeStep() {
  this->previousTime = 0;
  this->currentTime = millis();
}

double TimeStep::getCurrentStep() {
  this->previousTime = this->currentTime;
  this->currentTime = millis();
  double delta = abs((this->currentTime - this->previousTime));
  return delta / 1000;
}

