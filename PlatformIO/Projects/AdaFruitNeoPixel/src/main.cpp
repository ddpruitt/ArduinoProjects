#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6     // Pin for data
#define LEDS 32   // How many LEDs?
#define ROWS 4    // count LEDs downward
#define COLUMS 8  //Count your LEDS to the right
#define SPEED 100 //faster the lower the number

#define RANDLOW 0  //low value for random numbers
#define RANDHIGH 5 //High value for random numbers

void colorWipe(uint32_t c, uint8_t wait);
void colorWipeRow(uint32_t c, uint8_t wait);
void colorWipeColumn(uint32_t c, uint8_t wait);

long randNumber;
long randNumber2;
long randNumber3;

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
  //random numbers from 1 to 255
  randNumber = random(RANDLOW, RANDHIGH);
  randNumber2 = random(RANDLOW, RANDHIGH);
  randNumber3 = random(RANDLOW, RANDHIGH);

  colorWipe(strip.Color(0,0,randNumber), SPEED);
  colorWipeRow(strip.Color(randNumber3, 0, 0), SPEED);
  colorWipeColumn(strip.Color(0, randNumber2, 0), SPEED);
}

// Fills a colums of dots one after the other with a one single color then another color.
void colorWipeColumn(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < COLUMS; i++)
  {
    for (uint16_t r = 0; r < ROWS; r++)
    {
      strip.setPixelColor((r * COLUMS + i), c);
    }
    strip.show();
    delay(wait);
  }
}

// Fills a colums of dots one after the other with a one single color then another color.
void colorWipeRow(uint32_t c, uint8_t wait)
{
  for (uint16_t r = 0; r < ROWS; r++)
  {
    for (uint16_t y = 0; y < COLUMS; y++)
    {
      strip.setPixelColor((r * COLUMS + y), c);
    }
    strip.show();
    delay(wait);
  }
}

// Fills a colums of dots one after the other with a one single color then another color.
void colorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < LEDS; i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
