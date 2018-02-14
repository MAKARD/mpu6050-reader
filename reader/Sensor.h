
#include "MPU6050.h"

struct AccelerometerData {
    int16_t x, y, z;
};

struct GyroscopeData {
    int16_t x, y, z;
};

class Sensor {
    public:
        Sensor(int, int);

        int pinOne;
        int pinTwo;

        MPU6050 sensor;
        AccelerometerData accelerometer;
        GyroscopeData gyroscope;

        string stringifyData();

        void readAcceleration();
        void readRotation();
};
