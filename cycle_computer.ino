//The 10 Dof sample sketch for reading the BMP085 and IMUs raw data

#include "dof.h"
#include "gps.h"
#include "tft.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Wire.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <HMC5883L.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

 


int color = 0;
 
void setup(){
 
  Serial.begin(9600);
  //Wire.begin();
 
   prepare10dof();
   prepareTft();
}
 
void loop(){
   
  readDataFrom10dof();
  displayDateTime(day(), month(), year(), hours(), minutes(), seconds());
  displayPitchRoll(angles[1], angles[2]);
  displayHeading(angles[0], angle());
  delay(300);
}



