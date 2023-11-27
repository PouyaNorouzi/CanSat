#include <QMC5883LCompass.h>
#include "CanSat_Compass.h"

QMC5883LCompass compass;

int CanSat_Comp::getaz(double &azimuth, double &heading){

  compass.init();
  //compass.setCalibrationOffsets(-210.00, 1100.00, 150.00);
  //compass.setCalibrationScales(0.91, 1.25, 0.91);
  compass.setCalibrationOffsets(315.00, 90.00, -53.00);
  compass.setCalibrationScales(1.06, 0.98, 0.96);
  compass.read();

  azimuth=compass.getAzimuth();

  //1:S  2:SSE  3:SE  4:ESE  5:E  6:ENE  7:NE  8:NNE  9:N  10:NNW  11:NW  12:WNW  13:W  14:WSW  15:SW  16:SSW
  if ((azimuth>168)||(azimuth<=-168))
    heading = 1;
  else if ((azimuth>155)&&(azimuth<=168))
    heading = 2;
  else if ((azimuth>123)&&(azimuth<=155))
    heading = 3;
  else if ((azimuth>101)&&(azimuth<=123))
    heading = 4;
  else if ((azimuth>78)&&(azimuth<=101))
    heading = 5;
  else if ((azimuth>56)&&(azimuth<=78))
    heading = 6;
  else if ((azimuth>33)&&(azimuth<=56))
    heading = 7;
  else if ((azimuth>11)&&(azimuth<=33))
    heading = 8;
  else if ((azimuth>-11)&&(azimuth<=11))
    heading = 9;
  else if ((azimuth>-33)&&(azimuth<=-11))
    heading = 10;
  else if ((azimuth>-56)&&(azimuth<=-33))
    heading = 11;
  else if ((azimuth>-78)&&(azimuth<=-56))
    heading = 12;
  else if ((azimuth>-101)&&(azimuth<=-78))
    heading = 13;
  else if ((azimuth>-123)||(azimuth<=-101))
   heading = 14;
  else if ((azimuth>-155)&&(azimuth<=-123))
    heading = 15;
  else if ((azimuth>-168)&&(azimuth<=-155))
    heading = 16;

}