
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
        bool initialized;
        MPU6050 sensor;
        
        GyroscopeData gyroscope;
        AccelerometerData accelerometer;

        void readRotation(void);
        void readAcceleration(void);
        String serializeData(void);
};
