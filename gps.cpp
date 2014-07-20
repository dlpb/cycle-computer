#include <SoftwareSerial.h>

#include "gps.h"
#include "SPI.h"

//GPS Requirements
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>


boolean interrupt = false;


//prepare the GPS
SoftwareSerial mySerial(8,7);
Adafruit_GPS GPS(&mySerial);

void prepareGps(){
  GPS.begin(9600);
  tft.println("Loading GPS");
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
}
