//The 10 Dof sample sketch for reading the BMP085 and IMUs raw data

#include "dof.h"

#include "tft.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Wire.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <HMC5883L.h>

 



 
void setup(){
 
  Serial.begin(9600);
  //Wire.begin();
 
   prepare10dof();
   prepareTft();
}
 
void loop(){
   
  readDataFrom10dof();
  displayPitchRoll(angles[1], angles[2]);   
  delay(300);
}



