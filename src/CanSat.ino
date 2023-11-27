#include "CanSat_bmp180.h"
#include "CanSat_Compass.h"
#include "CanSat_Gyro.h"
#include "CanSat_SDc.h"
#include <SPI.h>
#include <SD.h>

File myFile1;

const int chipSelect = 53;

CanSat_BMP180 bmp;
CanSat_Comp comp;
CanSat_gyro acce;
CanSat_save senddat;

int j=0;
double data[15];
String data1;
String data2;
String data3;
double gpstime;
double gpsdate;
double latitude;
double longitude;
double altitude;
double gpsknots;
double gpstrack;
char latNS, lonEW;
char gpsstatus;
int fixquality;
int numsatelites;        
volatile int ptr = 0;
volatile bool flag = true;
volatile char redbuffer[120];
volatile char blubuc:\Users\NR\Desktop\C1.TXTffer[120];

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  SD.begin();
  
  SelectSentences();
}

void loop() {
  listen();

  data[13] = latitude;
  data[14] = longitude;
  data[0] = gpstime;
  data[1] = gpsdate;

  bmp.getpress(data[2], data[3],  data[4]);
  comp.getaz(data[5], data[6]);
  acce.getacc(data[7], data[8], data[9], data[10], data[11], data[12]);
  data1 = "Date:" + String(data[1]) + "\t|Time:" +
                    String(data[0]) + "\t|Temp.: " + 
                    String(data[2]) + " °C\t|pres.: " + 
                    String(data[3]) + "mbar";
  data2 =  "\t|Alt.: " + String(data[4]) + " m\t|Head: " + 
                         String(data[6]) + "\t|ax: " +
                         String(data[7]) + " m^2/s\t|ay: " + 
                         String(data[8]) + " m^2/s" ;
  data3 =  "\t|az: " + String(data[9]) + " m^2/s\t|Lat.: " + 
                       String(data[13],8) + " N\t|Long.: " + 
                       String(data[14],8) + " E\n";
  Serial.print("Date.:");  Serial.print(data[1]); Serial.print(" \t|");
  Serial.print("Time.:");  Serial.print(data[0]); Serial.print(" \t|");
  Serial.print("Temp.:");  Serial.print(data[2]); Serial.print(" C\t|");
  Serial.print("Pressure:");  Serial.print(data[3]);  Serial.print(" mbar\t|");
  Serial.print("Alt.:");  Serial.print(data[4]);  Serial.print(" m\t|");
  Serial.print("Heading:");  Serial.print(data[6]);  Serial.print(" \t|");
  Serial.print("ax:");  Serial.print(data[7]);  Serial.print(" m^2/s\t|");
  Serial.print("ay:");  Serial.print(data[8]);  Serial.print(" m^2/s\t|");
  Serial.print("az:");  Serial.print(data[9]);  Serial.print(" m^2/s\t|");
  Serial.print("Lat.:");
  Serial.print(data[13],8);
  Serial.print(" N\t|");
  Serial.print("Long.:");
  Serial.print(data[14],8);
  Serial.println(" E");
  //senddat.savedata(dataa);
  myFile1 = SD.open("C2.txt", FILE_WRITE);
  if (myFile1){
  myFile1.print(data1);
  myFile1.print(data2);
  myFile1.print(data3);

      myFile1.close();}
      else{
            Serial.println("error opening test.txt");

      }
}

void listen(){

  while (Serial2.available())
  {
     read(Serial2.read());
  }
}

void read(char nextChar){

  if (nextChar == '$') {
    
    flag ? redbuffer[ptr] = '\0' : blubuffer[ptr] = '\0';

    ptr = 0;
  }

  if (nextChar == '\n') {

    if (flag) {
      flag = false;
      
      redbuffer[ptr] = '\0';

      if (CheckSum((char*) redbuffer )) {parseString((char*) redbuffer );}
    }
    else
    {
      flag = true;
      
      blubuffer[ptr] = '\0';

      if (CheckSum((char*) blubuffer )) {parseString((char*) blubuffer );}
    }   
    ptr = 0; 
  }

  flag ? redbuffer[ptr] = nextChar : blubuffer[ptr] = nextChar;

  if (ptr < 119) ptr++;

}

bool CheckSum(char* msg) {

  // Check the checksum
  //$GPGGA,.........................0000*6A
  
  // Length of the GPS message
  int len = strlen(msg);

  // Does it contain the checksum, to check
  if (msg[len-4] == '*') {

  // Read the checksum from the message
  int cksum = 16 * Hex2Dec(msg[len-3]) + Hex2Dec(msg[len-2]);

  // Loop over message characters
  for (int i=1; i < len-4; i++) {
          cksum ^= msg[i];
      }

  // The final result should be zero
  if (cksum == 0){
    return true;
  }
  }

  return false;
}


float DegreeToDecimal(float num, byte sign)
{
   // Want to convert DDMM.MMMM to a decimal number DD.DDDDD

   int intpart= (int) num;
   float decpart = num - intpart;

   int degree = (int)(intpart / 100);
   int mins = (int)(intpart % 100);

   if (sign == 'N' || sign == 'E')
   {
     // Return positive degree
     return (degree + (mins + decpart)/60);
   }   
   // Return negative degree
   return -(degree + (mins + decpart)/60);
}

void parseString(char* msg) {

  messageGGA(msg);
  messageRMC(msg);
}


void messageGGA(char* msg) 
{
  // Ensure the checksum is correct before doing this
  // Replace all the commas by end-of-string character '\0'
  // Read the first string
  // Knowing the length of the first string, can jump over to the next string
  // Repeat the process for all the known fields.
  
  // Do we have a GGA message?
  if (!strstr(msg, "GGA")) return;

  // Length of the GPS message
  int len = strlen(msg);

  // Replace all the commas with end character '\0'
  for (int j=0; j<len; j++){
    if (msg[j] == ',' || msg[j] == '*'){
      msg[j] = '\0';
    }
  }

  // Allocate working variables
  int i = 0;

  //$GPGGA

  // GMT time  094728.000
  i += strlen(&msg[i])+1;
  gpstime = atof(&msg[i]);
  
  // Latitude
  i += strlen(&msg[i])+1;
  latitude = atof(&msg[i]);
  
  // North or South (single char)
  i += strlen(&msg[i])+1;
  latNS = msg[i];
  if (latNS == '\0') latNS = '.';
  
  // Longitude
  i += strlen(&msg[i])+1;
  longitude = atof(&msg[i]);
  
  // East or West (single char)
  i += strlen(&msg[i])+1;
  lonEW = msg[i];
  if (lonEW == '\0') lonEW = '.';  
  
  // Fix quality (1=GPS)(2=DGPS)
  i += strlen(&msg[i])+1;
  fixquality = atof(&msg[i]);   
      
  // Number of satellites being tracked
  i += strlen(&msg[i])+1;
  numsatelites = atoi(&msg[i]); 
  
  // Horizontal dilution of position
  i += strlen(&msg[i])+1;
  
  // Altitude
  i += strlen(&msg[i])+1;
  altitude = atof(&msg[i]);     
  
  // Height of geoid (mean sea level)
  i += strlen(&msg[i])+1;
  
  // Time in seconds since last DGPS update
  i += strlen(&msg[i])+1;
  
  // DGPS station ID number
  i += strlen(&msg[i])+1;
  
  // Convert from degrees and minutes to degrees in decimals
  latitude = DegreeToDecimal(latitude, latNS);
  longitude = DegreeToDecimal(longitude, lonEW);   
}


void messageRMC(char* msg) 
{
  // Ensure the checksum is correct before doing this
  // Replace all the commas by end-of-string character '\0'
  // Read the first string
  // Knowing the length of the first string, can jump over to the next string
  // Repeat the process for all the known fields.
  
  // Do we have a RMC message?
  if (!strstr(msg, "RMC")) return;

  // Length of the GPS message
  int len = strlen(msg);

  // Replace all the commas with end character '\0'
  for (int j=0; j<len; j++){
    if (msg[j] == ',' || msg[j] == '*'){
      msg[j] = '\0';
    }
  }

  // Allocate working variables
  int i = 0;

  //$GPRMC

  // GMT time  094728.000
  i += strlen(&msg[i])+1;
  gpstime = atof(&msg[i]);

  // Status A=active or V=Void.
  i += strlen(&msg[i])+1;
  gpsstatus = msg[i];

  // Latitude
  i += strlen(&msg[i])+1;
  latitude = atof(&msg[i]);

  // North or South (single char)
  i += strlen(&msg[i])+1;
  latNS = msg[i];
  if (latNS == '\0') latNS = '.';

  // Longitude
  i += strlen(&msg[i])+1;
  longitude = atof(&msg[i]);

  // East or West (single char)
  i += strlen(&msg[i])+1;
  lonEW = msg[i];
  if (lonEW == '\0') lonEW = '.';               

  // // Speed over the ground in knots
  i += strlen(&msg[i])+1;
  gpsknots = atof(&msg[i]);

  // Track angle in degrees True North
  i += strlen(&msg[i])+1;
  gpstrack = atof(&msg[i]); 
  
  // Date - 31st of March 2018
  i += strlen(&msg[i])+1;
  gpsdate = atof(&msg[i]); 
                     
  // Magnetic Variation
  
  // Convert from degrees and minutes to degrees in decimals
  latitude = DegreeToDecimal(latitude, latNS);
  longitude = DegreeToDecimal(longitude, lonEW);
}

// Convert HEX to DEC
int Hex2Dec(char c) {

  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  else if (c >= 'A' && c <= 'F') {
    return (c - 'A') + 10;
  }
  else {
    return 0;
  }
}


void AllSentences()
{
  // NMEA_GLL output interval - Geographic Position - Latitude longitude
  // NMEA_RMC output interval - Recommended Minimum Specific GNSS Sentence
  // NMEA_VTG output interval - Course Over Ground and Ground Speed
  // NMEA_GGA output interval - GPS Fix Data
  // NMEA_GSA output interval - GNSS DOPS and Active Satellites
  // NMEA_GSV output interval - GNSS Satellites in View

  // Enable $PUBX,40,GLL,0,1,0,0*5D
  Serial2.println("$PUBX,40,GLL,0,1,0,0*5D");
  delay(100);

  // Enable $PUBX,40,RMC,0,1,0,0*46
  Serial2.println("$PUBX,40,RMC,0,1,0,0*46");
  delay(100);
  
  // Enable $PUBX,40,VTG,0,1,0,0*5F
  Serial2.println("$PUBX,40,VTG,0,1,0,0*5F");
  delay(100);

  // Enable $PUBX,40,GGA,0,1,0,0*5B
  Serial2.println("$PUBX,40,GGA,0,1,0,0*5B");
  delay(100);
  
  // Enable $PUBX,40,GSA,0,1,0,0*4F
  Serial2.println("$PUBX,40,GSA,0,1,0,0*4F");
  delay(100);  

  // Enable $PUBX,40,GSV,0,5,0,0*5C
  Serial2.println("$PUBX,40,GSV,0,5,0,0*5C");
  delay(100);
}


void SelectSentences()
{
  // NMEA_GLL output interval - Geographic Position - Latitude longitude
  // NMEA_RMC output interval - Recommended Minimum Specific GNSS Sentence
  // NMEA_VTG output interval - Course Over Ground and Ground Speed
  // NMEA_GGA output interval - GPS Fix Data
  // NMEA_GSA output interval - GNSS DOPS and Active Satellites
  // NMEA_GSV output interval - GNSS Satellites in View

  // Enable $PUBX,40,RMC,0,1,0,0*46
  Serial2.println("$PUBX,40,RMC,0,1,0,0*46");
  delay(100);

  // Enable $PUBX,40,GGA,0,1,0,0*5B
  Serial2.println("$PUBX,40,GGA,0,1,0,0*5B");
  delay(100);

  // disable $PUBX,40,GLL,0,0,0,0*5C
  Serial2.println("$PUBX,40,GLL,0,0,0,0*5C");
  delay(100);
  
  // disable $PUBX,40,VTG,0,0,0,0*5E
  Serial2.println("$PUBX,40,VTG,0,0,0,0*5E");
  delay(100);
  
  // disable $PUBX,40,GSA,0,0,0,0*4E
  Serial2.println("$PUBX,40,GSA,0,0,0,0*4E");
  delay(100);  

  // disable $PUBX,40,GSV,0,0,0,0*59
  Serial2.println("$PUBX,40,GSV,0,0,0,0*59");
  delay(100);
  
}


void SelectGGAonly()
{
  // NMEA_GLL output interval - Geographic Position - Latitude longitude
  // NMEA_RMC output interval - Recommended Minimum Specific GNSS Sentence
  // NMEA_VTG output interval - Course Over Ground and Ground Speed
  // NMEA_GGA output interval - GPS Fix Data
  // NMEA_GSA output interval - GNSS DOPS and Active Satellites
  // NMEA_GSV output interval - GNSS Satellites in View

  // Enable $PUBX,40,GGA,0,1,0,0*5B
  Serial2.println("$PUBX,40,GGA,0,1,0,0*5B");
  delay(100);

  // disable $PUBX,40,RMC,0,0,0,0*47
  Serial2.println("$PUBX,40,RMC,0,0,0,0*47");
  delay(100);

  // disable $PUBX,40,GLL,0,0,0,0*5C
  Serial2.println("$PUBX,40,GLL,0,0,0,0*5C");
  delay(100);

  // disable $PUBX,40,VTG,0,0,0,0*5E
  Serial2.println("$PUBX,40,VTG,0,0,0,0*5E");
  delay(100);
  
  // disable $PUBX,40,GSA,0,0,0,0*4E
  Serial2.println("$PUBX,40,GSA,0,0,0,0*4E");
  delay(100);  

  // disable $PUBX,40,GSV,0,0,0,0*59
  Serial2.println("$PUBX,40,GSV,0,0,0,0*59");
  delay(100);
  
}