#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library


// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A11 // Chip Select goes to Analog 3
#define LCD_CD A10 // Command/Data goes to Analog 2
#define LCD_WR A9 // LCD Write goes to Analog 1
#define LCD_RD A8 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define DARK_GREY  0x7BEF
#define LIGHT_GREY 0xBDF7

#define PITCH_ROLL_X 20
#define PITCH_ROLL_Y 20
#define PITCH_ROLL_WIDTH 80
#define PITCH_ROLL_HEIGHT 80

#define DATE_TIME_X 60
#define DATE_TIME_Y 0
#define DATE_TIME_WIDTH 150
#define DATE_TIME_HEIGHT 16

#define HEADING_X 100
#define HEADING_Y 20
#define HEADING_WIDTH 80
#define HEADING_HEIGHT 80


void prepareTft();
void fill(int color);
void prepareInitialScreen();
void clearPart(int, int, int, int, int);
void displayPitchRoll(float pitch, float roll);
void displayDateTime(int day, int month, int year, int hour, int minute, int second);
void displayHeading(int heading, int gps);
