#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6     // Pin for data
#define LEDS 32   // How many LEDs?
#define ROWS 4    // count LEDs downward
#define COLUMNS 8 //Count your LEDS to the right
#define SPEED 100 //faster the lower the number

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t c000 = strip.Color(0, 0, 0); // Off basically

uint16_t neoPixelIndex[ROWS][COLUMNS] =
    {
        {0, 1, 2, 3, 4, 5, 6, 7},
        {8, 9, 10, 11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20, 21, 22, 23},
        {24, 25, 26, 27, 28, 29, 30, 31}
    };

uint16_t pattern01[ROWS][COLUMNS] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 2, 0, 0, 0},
        {0, 0, 0, 3, 4, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

uint16_t pattern02[ROWS][COLUMNS] =
    {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

uint16_t pattern03[ROWS][COLUMNS] =
    {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0}
    };

uint16_t getNeoPixel(uint16_t row, uint16_t column, uint16_t offsetRow, uint16_t offsetColumn)
{
  return COLUMNS * ((row + offsetRow) % ROWS) + (column + offsetColumn) % COLUMNS;
}

uint16_t getNeoPixel(uint16_t row, uint16_t column)
{
  return getNeoPixel(row, column, 0, 0);
}

void setNeoPixelMatrix(uint16_t row, uint16_t column, uint32_t c)
{
  strip.setPixelColor(neoPixelIndex[row][column], c);
  strip.show();
  delay(SPEED);
}

void setNeoPixelColor(uint16_t row, uint16_t column, uint32_t c)
{
  strip.setPixelColor(getNeoPixel(row,column), c);
  strip.show();
  delay(SPEED);
}

void setPixelColorPattern(uint16_t pattern[ROWS][COLUMNS], uint32_t colors[], size_t lenOfColors)
{

  for (uint16_t row = 0; row < ROWS; row++)
  {
    for (uint16_t col = 0; col < COLUMNS; col++)
    {
      //strip.setPixelColor(getNeoPixel(row, col), colors[pattern[row][col]]);
      if(lenOfColors <= pattern[row][col]  || 0 > pattern[row][col])
      {
        strip.setPixelColor(getNeoPixel(row, col), strip.Color(0, 0, 0));
        continue;
      }
      strip.setPixelColor(getNeoPixel(row, col), colors[pattern[row][col]]);
    }

  }
  strip.show();
  delay(SPEED);
}

void setup()
{
  Serial.begin(57600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  // uint32_t c1 = strip.Color(4, 0, 0);
  // uint32_t c2 = strip.Color(0, 4, 0);

  // setNeoPixelMatrix(1,3,c1);
  // setNeoPixelMatrix(3,5,c2);

  // setNeoPixelColor(3,5,c2);
  // setNeoPixelColor(3,5,c000);

  uint32_t colors[4];
  colors[0] = strip.Color(0,0,0);
  colors[1] = strip.Color(0,4,0);
  colors[2] = strip.Color(0,0,4);
  colors[3] = strip.Color(4,0,0);

  uint32_t redColors[2] = { strip.Color(0,0,0), strip.Color(4,0,0) };
  uint32_t blueColors[2] = { strip.Color(0,0,0), strip.Color(0,0,4) };
  uint32_t greenColors[2] = { strip.Color(0,0,0), strip.Color(0,4,0) };

  //setPixelColorPattern(pattern01, colors, 4);
  //delay(SPEED);
  //setPixelColorPattern(pattern02, colors, 4);
  //delay(SPEED);

  setPixelColorPattern(pattern02, blueColors, 2);
  delay(SPEED);
  setPixelColorPattern(pattern03, redColors, 2);
  delay(SPEED);

}