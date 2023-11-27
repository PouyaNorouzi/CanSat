#ifndef CanSat_Gyro
#define CanSat_Gyro

#include <Arduino.h>

class CanSat_gyro{
    public:
      double getacc(double &accx,double &accy,double &accz,double &x,double &y,double &z);
    private:

};

#endif