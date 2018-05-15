#include "MPU6050.h"

struct AxisData {
  double x, y, z;
};

class Sensor {
  public:
    Sensor(int, int);

    int pinOne;
    int pinTwo;
    MPU6050 sensor;

    AxisData gyroscope;
    AxisData accelerometer;

    void readRotation();
    void readAcceleration();

    void scaleRotation(int);
    void scaleAcceleration(int);

    String serializeData();
};
