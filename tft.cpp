
#include "tft.h"


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library


// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).


#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin



// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//#define TFT_CS 10
//#define TFT_DC 9
//#define TFT_MOSI 11
//#define TFT_CLK 13
//#define TFT_RST -1
//#define TFT_MISO 12


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);



void prepareTft()
{
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif

  tft.reset();

  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }

  tft.begin(identifier);
  tft.fillScreen(BLACK);
  prepareInitialScreen();

}


void fill(int color) { tft.fillScreen(color); }

void clearPart(int x, int y, int w, int h, int color)
{
  
  tft.fillRect(x,y,w,h,color);
}

void prepareInitialScreen()
{
  //status bar
  clearPart(0,0,240, DATE_TIME_HEIGHT, LIGHT_GREY);
  tft.drawLine(0,DATE_TIME_HEIGHT+1, 240, DATE_TIME_HEIGHT+1, DARK_GREY);
  
  //pitch roll
  clearPart(PITCH_ROLL_X, PITCH_ROLL_Y, PITCH_ROLL_WIDTH, PITCH_ROLL_HEIGHT, DARK_GREY);
  
  //heading
  clearPart(HEADING_X, HEADING_Y, HEADING_WIDTH, HEADING_HEIGHT, BLUE);
}

double scale(double valueIn, double baseMin, double baseMax, double limitMin, double limitMax)
{
        return ((limitMax - limitMin) * (valueIn - baseMin) / (baseMax - baseMin)) + limitMin;
}

void displayPitchRoll(float pitch, float roll)
{
  
  double scaled = -1 * scale(pitch, -180, 180, -40, 40);
  
  int halfWidth = PITCH_ROLL_WIDTH / 2;
  int halfHeight = PITCH_ROLL_HEIGHT / 2;
  
  int x = PITCH_ROLL_X + halfWidth;
  int y = PITCH_ROLL_Y + halfHeight;
  double pi = 3.14159;
  double rad = (roll * pi) / 180;
  //right
  int endX = x + (halfWidth * cos(rad));
  int endY = y + (halfHeight * sin(rad));
  int startX = x - (halfWidth * cos(rad));
  int startY = y - (halfHeight * sin(rad));
  
  if(startX < PITCH_ROLL_X) startX = PITCH_ROLL_X;
  if(startY < PITCH_ROLL_Y) startX = PITCH_ROLL_Y;
  if(endX > PITCH_ROLL_X + PITCH_ROLL_WIDTH) endX = PITCH_ROLL_X + PITCH_ROLL_WIDTH;
  if(endX > PITCH_ROLL_Y + PITCH_ROLL_WIDTH) endY = PITCH_ROLL_Y + PITCH_ROLL_WIDTH;
  
//if(endX > startX) 
  { 
    tft.fillTriangle(startX, startY, endX, endY, endX, startY, BLUE);
    tft.fillRect(PITCH_ROLL_X, PITCH_ROLL_Y, PITCH_ROLL_WIDTH, PITCH_ROLL_HEIGHT - endX, GREEN);
  }
  //else 
  {
    tft.fillTriangle(startX, startY, endX, startY, endX, endY, YELLOW);
    tft.fillRect(PITCH_ROLL_X, PITCH_ROLL_Y + startY, PITCH_ROLL_WIDTH, PITCH_ROLL_HEIGHT - startY, RED);
  } 
 // clearPart(PITCH_ROLL_X, PITCH_ROLL_Y, PITCH_ROLL_WIDTH, PITCH_ROLL_HEIGHT, DARK_GREY);
  tft.setCursor(PITCH_ROLL_X,PITCH_ROLL_Y);
  
  
  
  tft.drawLine(startX, startY + scaled, endX, endY + scaled , BLACK);
  
//  tft.setTextSize(2);
//  tft.setTextColor(WHITE);
//  tft.println(pitch);
//  tft.println(roll);
//  tft.println(scaled);
}

void displayDateTime(int day, int month, int year, int hour, int minute, int seconds)
{
  clearPart(DATE_TIME_X, DATE_TIME_Y, DATE_TIME_WIDTH,DATE_TIME_HEIGHT, LIGHT_GREY);
  tft.setCursor(DATE_TIME_X,DATE_TIME_Y);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print(day);
  tft.print("/");
  tft.print(month);
  tft.print("/");
  tft.print(year);
  tft.print(" ");
  tft.print(hour);
  tft.print(":");
  tft.print(minute);
  tft.print(":");
  tft.println(seconds);
}

void displayHeading(int heading, int gps)
{
  if(heading < 0) { heading = heading + 360; }
  clearPart(HEADING_X, HEADING_Y, HEADING_WIDTH, HEADING_HEIGHT, BLUE);
  tft.setCursor(HEADING_X, HEADING_Y);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println(heading);
  tft.setCursor(HEADING_X + 30, HEADING_Y + 30);
  tft.setTextSize(2);
  tft.println(gps);
  tft.setCursor(HEADING_X + 30, HEADING_Y + 50); 
  
  if(heading > -1 && heading < 11.25) { tft.println("N"); }
  else if(heading > 348.75 && heading < 360) { tft.println("N"); }
  else if(heading > 11.25 && heading < 33.75) { tft.println("NNE"); }
  else if(heading > 33.75 && heading < 56.25) { tft.println("NE"); }
  else if(heading > 56.25 && heading < 78.75) { tft.println("ENE"); }
  else if(heading > 78.75 && heading < 101.25) { tft.println("E"); }
  else if(heading > 101.25 && heading < 123.75) { tft.println("ESE"); }
  else if(heading > 123.75 && heading < 146.25) { tft.println("SE"); }
  else if(heading > 146.25 && heading < 168.75) { tft.println("SSE"); }
  else if(heading > 168.75 && heading < 191.25) { tft.println("S"); }
  else if(heading > 191.25 && heading < 213.75) { tft.println("SSW"); }
  else if(heading > 213.75 && heading < 236.25) { tft.println("SW"); }
  else if(heading > 236.25 && heading < 258.75) { tft.println("WSW"); }
  else if(heading > 258.75 && heading < 281.25) { tft.println("W"); }
  else if(heading > 281.25 && heading < 303.75) { tft.println("WNW"); }
  else if(heading > 303.75 && heading < 326.25) { tft.println("NW"); }
  else if(heading > 326.25 && heading < 34.75) { tft.println("NNW"); }

  
}

