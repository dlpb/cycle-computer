#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

#include "SPI.h"

//GPS Requirements
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

//10dof Requirements

#define GPSECHO false

extern boolean interrupt;
void useInterrupt(boolean);

extern SoftwareSerial mySerial;

void prepareGps();
extern uint32_t timer;

int seconds();
int minutes();
int hours();
int day();
int month();
int year();

int fix();
int quality();
int lat();
int lon();
int knots();
int angle();
int gps_alt();
int sats();

int mph();
int kph();
int mps();
