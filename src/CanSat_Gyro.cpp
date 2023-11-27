#include <Wire.h>
#include "CanSat_Gyro.h"

const int MPU_ADDR = 0x68;

double accelerometer_x, accelerometer_y, accelerometer_z;
double gyro_x, gyro_y, gyro_z;
double temperature;

char tmp_str[7];

double kalman (double &a){
  static const double r=40;
  static const double h=1;
  static double q=10;
  static double p=0;
  static double ahat=0;
  static double k=0;
  k=p*h/(h*p*h+r);
  a=ahat+k*(a-h*ahat);
  p=(1-k*h)*p+q;
}

double CanSat_gyro::getacc(double &accelerometer_x,double &accelerometer_y,double &accelerometer_z,double &gyro_x,double &gyro_y,double &gyro_z){

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7*2, true);

  accelerometer_x = Wire.read()<<8 | Wire.read();
  accelerometer_y = Wire.read()<<8 | Wire.read();
  accelerometer_z = Wire.read()<<8 | Wire.read();
  temperature = Wire.read()<<8 | Wire.read();
  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read();
  gyro_z = Wire.read()<<8 | Wire.read();
  
  kalman(accelerometer_x);
  kalman(accelerometer_y);
  kalman(accelerometer_z);
  kalman(gyro_x);
  kalman(gyro_y);
  kalman(gyro_z);
}