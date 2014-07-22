#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#include "gps.h"
#include "SPI.h"

//GPS Requirements


boolean interrupt = false;


//prepare the GPS
SoftwareSerial mySerial(8,7);
Adafruit_GPS GPS(&mySerial);

void prepareGps(){
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0

    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    interrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    interrupt = false;
  }
}

uint32_t timer = millis();


int seconds() { return GPS.seconds; }
int minutes() { return GPS.minute;  }
int hours()   { return GPS.hour;    }
int day()     { return GPS.day;     }
int month()   { return GPS.month;   }
int year()    { return GPS.year;    }

int fix()     { return GPS.fix;     }
int quality() { return GPS.fixquality; }
int lat()     { return GPS.lat;     }
int lon()     { return GPS.lon;     }
int knots()   { return GPS.speed;   }
int angle()   { return GPS.angle;   }
int gps_alt() { return GPS.altitude; }
int sats()    { return GPS.satellites; }

int mph()     { return knots() * 1.1507794480230764; }
int kph()     { return knots() * 1.852000001563088; }
int mps()     { return knots() * 0.5144444444446045; }

