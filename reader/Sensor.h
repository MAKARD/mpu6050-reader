#include "MPU6050.h"

struct AxisData {
    int16_t x, y, z;
};

class Sensor {
    public:
        Sensor(int, int);

        int pinOne;
        int pinTwo;
        bool initialized;
        MPU6050 sensor;

        AxisData angles;
        AxisData gyroscope;
        AxisData accelerometer;

        void readRotation();
        void readAcceleration();

        void scaleRotation(int16_t);
        void calculateAngles(double);
        
        String serializeData();
   private: 
        AxisData gyroAngles;
};
