#include <Wire.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <HMC5883L.h>

extern float angles[3];
extern float heading;

extern short temperature;
extern long pressure;

#define BMP085_ADDRESS 0x77  // I2C address of BMP085

extern const unsigned char OSS;  // Oversampling Setting

extern HMC5883L compass;

// Calibration values
extern int ac1;
extern int ac2; 
extern int ac3; 
extern unsigned int ac4;
extern unsigned int ac5;
extern unsigned int ac6;
extern int b1; 
extern int b2;
extern int mb;
extern int mc;
extern int md;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
extern long b5; 


void getHeading();
void bmp085Calibration();
short bmp085GetTemperature(unsigned int ut);
long bmp085GetPressure(unsigned long up);
char bmp085Read(unsigned char address);
int bmp085ReadInt(unsigned char address);
unsigned int bmp085ReadUT();
unsigned long bmp085ReadUP();

void prepare10dof();
void readDataFrom10dof();
void print10dofData();



