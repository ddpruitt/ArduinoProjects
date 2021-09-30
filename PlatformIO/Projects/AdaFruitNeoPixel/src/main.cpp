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

#define RANDLOW 0  //low value for random numbers
#define RANDHIGH 4 //High value for random numbers

void setAllColors(uint32_t c, uint8_t wait);
void setRowColor(uint32_t c, uint16_t row, uint8_t wait);
void setColumnColor(uint32_t c, uint16_t column, uint8_t wait);

void colorWipeByIndex(uint32_t c, uint8_t wait);
void colorWipeByIndex(uint32_t c1, uint32_t c2, uint8_t wait);
void colorWipeByRow(uint32_t c, uint8_t wait);
void colorWipeByColumn(uint32_t c, uint8_t wait);

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(57600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  // Some example procedures showing how to display to the pixels:
  //random numbers from RANDLOW to RANDHIGH
  uint32_t colors[LEDS];
  for (uint16_t i = 0; i < LEDS; i++)
  {
    colors[i] = strip.Color(random(RANDLOW, RANDHIGH), random(RANDLOW, RANDHIGH), random(RANDLOW, RANDHIGH));
  }

  uint32_t c0;
  c0 = strip.Color(0, 0, 0);

  for (uint16_t i = 0; i < LEDS; i++)
  {
    setAllColors(colors[i], SPEED);
  }

  setAllColors(c0, SPEED);

  for (uint16_t i = 0; i < LEDS; i += 2)
  {
    colorWipeByRow(colors[i], SPEED);
    colorWipeByColumn(colors[i + 1], SPEED);
  }

  // colorWipe(colors[2], SPEED);
  // colorWipe(colors[3], SPEED);
  // colorWipe(colors[4], SPEED);

  // colorWipe(c1, c2, SPEED);
  // colorWipeColumn(c0, SPEED);
  // colorWipe(c3, c1, SPEED);
  // colorWipeColumn(c0, SPEED);
  // colorWipe(c2, c3, SPEED);
  // colorWipeColumn(c0, SPEED);

  // setRowColor(c1, 0, SPEED);
  // setRowColor(c1, 1, SPEED);
  // setRowColor(c1, 2, SPEED);
  // setRowColor(c1, 3, SPEED);

  // setRowColor(c2, 0, SPEED);
  // setRowColor(c0, 3, SPEED);

  // setRowColor(c2, 1, SPEED);
  // setRowColor(c0, 0, SPEED);

  // setRowColor(c2, 2, SPEED);
  // setRowColor(c0, 1, SPEED);

  // setRowColor(c2, 3, SPEED);
  // setRowColor(c0, 2, SPEED);

  // setColumnColor(c3, 0, SPEED);
  // setColumnColor(c0, 7, SPEED);

  // setColumnColor(c3, 1, SPEED);
  // setColumnColor(c0, 0, SPEED);

  // setColumnColor(c3, 2, SPEED);
  // setColumnColor(c0, 1, SPEED);

  // setColumnColor(c3, 3, SPEED);
  // setColumnColor(c0, 2, SPEED);

  // setColumnColor(c3, 4, SPEED);
  // setColumnColor(c0, 3, SPEED);

  // setColumnColor(c3, 5, SPEED);
  // setColumnColor(c0, 4, SPEED);

  // setColumnColor(c3, 6, SPEED);
  // setColumnColor(c0, 5, SPEED);

  // setColumnColor(c3, 7, SPEED);
  // setColumnColor(c0, 6, SPEED);
}

void setAllColors(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < LEDS; i++)
  {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

void setRowColor(uint32_t c, uint16_t row, uint8_t wait)
{
  if (row < 0 || row >= ROWS)
    return;

  for (uint16_t i = 0; i < COLUMNS; i++)
  {
    strip.setPixelColor(row * COLUMNS + i, c);
  }
  strip.show();
  delay(wait);
}

void setColumnColor(uint32_t c, uint16_t column, uint8_t wait)
{
  if (column < 0 || column >= COLUMNS)
    return;

  for (uint16_t i = 0; i < ROWS; i++)
  {
    strip.setPixelColor(i * COLUMNS + column, c);
  }
  strip.show();
  delay(wait);
}

void colorWipeByColumn(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < COLUMNS; i++)
  {
    setColumnColor(c, i, wait);
  }
}

void colorWipeByRow(uint32_t c, uint8_t wait)
{
  for (uint16_t r = 0; r < ROWS; r++)
  {
    setRowColor(c, r, wait);
  }
}

void colorWipeByIndex(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < LEDS; i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void colorWipeByIndex(uint32_t c1, uint32_t c2, uint8_t wait)
{
  for (uint16_t i = 0; i < LEDS; i++)
  {
    strip.setPixelColor(i, c1);
    strip.setPixelColor(LEDS - 1 - i, c2);
    strip.show();
    delay(wait);
  }
}
