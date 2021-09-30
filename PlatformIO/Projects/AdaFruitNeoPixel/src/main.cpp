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

#define RANDLOW 1  //low value for random numbers
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
  // c0 turns off the LED
  uint32_t c0 = strip.Color(0, 0, 0);

  // an array equal to the number of LEDS with all random colors.
  uint32_t colors[LEDS];
  for (uint16_t i = 0; i < LEDS; i++)
  {
    colors[i] = strip.Color(random(RANDLOW, RANDHIGH), random(RANDLOW, RANDHIGH), random(RANDLOW, RANDHIGH));
  }

  // set each pixel directly and wait.
  for (uint16_t i = 0; i < LEDS; i++)
  {
    strip.setPixelColor(i, colors[i]);
    strip.show();
    delay(SPEED);
  }

  // clear the screen
  setAllColors(c0, SPEED);

  // set all the rows to a color then the columns
  for (uint16_t i = 0; i < LEDS; i += 2)
  {
    colorWipeByRow(colors[i], SPEED);
    setAllColors(c0, SPEED);

    colorWipeByColumn(colors[i + 1], SPEED);
    setAllColors(c0, SPEED);
  }

  // clear the screen
  setAllColors(c0, SPEED);

  for (uint16_t cidx = 0; cidx < LEDS; cidx+=2)
  {
    for (uint16_t i = 0; i < ROWS; i++)
    {
      setRowColor(colors[cidx], i, SPEED);
      setRowColor(c0, (i - 1) % ROWS, SPEED);
    }
    setAllColors(c0, SPEED);

    for (uint16_t i = 0; i < COLUMNS; i++)
    {
      setColumnColor(colors[cidx+1], i, SPEED);
      setColumnColor(c0, (i - 1) % COLUMNS, SPEED);
    }
    setAllColors(c0, SPEED);
  }

  // clear the screen
  setAllColors(c0, SPEED);

  // set all the LED's one at a time.
  colorWipeByIndex(strip.Color(2, 0, 0), SPEED);
  colorWipeByIndex(strip.Color(0, 2, 0), SPEED);
  colorWipeByIndex(strip.Color(0, 0, 2), SPEED);

  // set all the LED's one at a time from both ends
  colorWipeByIndex(strip.Color(2, 0, 0), strip.Color(1, 0, 1), SPEED);
  // clear the screen
  setAllColors(c0, SPEED);

  colorWipeByIndex(strip.Color(0, 2, 0), strip.Color(1, 0, 1), SPEED);
  // clear the screen
  setAllColors(c0, SPEED);

  colorWipeByIndex(strip.Color(0, 0, 2), strip.Color(1, 0, 1), SPEED);

  // clear the screen
  setAllColors(c0, SPEED);

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
