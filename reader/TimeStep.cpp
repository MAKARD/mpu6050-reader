#include "TimeStep.h"

TimeStep::TimeStep(double millis) {
    this->previousTime = 0;
    this->currentTime = millis;
    this->iterator = 1;
}

double TimeStep::getCurrentStep(double millis) {
    this->previousTime = this->currentTime;
    this->currentTime = millis;

    return (this->currentTime - this->previousTime) / 1000;
}

void TimeStep::tick() {
    this->iterator++;
}
