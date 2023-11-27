#include <SFE_BMP180.h>
#include "CanSat_bmp180.h"

SFE_BMP180 bmp180;

  int CanSat_BMP180::getpress(double &T, double &P, double &alt){
  bmp180.begin();
  char status;
  bool success = false;

  status = bmp180.startTemperature();

  if (status != 0) {
    delay(500);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        alt=44330*(1-pow(P/1013.25,1/5.255));
      }
    }
  }
  return(T,P,alt);
}