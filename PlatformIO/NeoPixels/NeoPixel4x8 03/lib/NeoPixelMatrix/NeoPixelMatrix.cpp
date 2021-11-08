#include <NeoPixelMatrix.h>

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
uint32_t cRed = strip.Color(4, 0, 0);
uint32_t cGreen = strip.Color(0, 4, 0);
uint32_t cBlue = strip.Color(0, 0, 4);
uint32_t cWhite = strip.Color(1, 1, 1);

uint32_t cRGBW[5] = { c000, cRed, cGreen, cBlue, cWhite };

uint32_t redColors[2] = { c000, cRed };
uint32_t blueColors[2] = { c000, cBlue };
uint32_t greenColors[2] = { c000, cGreen };
uint32_t whiteColors[2] = { c000, cWhite };

uint32_t redBlueColors[2] = { cBlue, cRed };
uint32_t blueRedColors[2] = { cRed, cBlue };

// The NeoPixel in this case is in a 4x8 matrix pattern.  To address individual
// neopixels you have to know its index.  The matrix to neopixel index looks like this:
//
// uint16_t neoPixelIndex[ROWS][COLUMNS] =
//   {
//       {0, 1, 2, 3, 4, 5, 6, 7},
//       {8, 9, 10, 11, 12, 13, 14, 15},
//       {16, 17, 18, 19, 20, 21, 22, 23},
//       {24, 25, 26, 27, 28, 29, 30, 31}
//   };
//
// The offset is if you want to shift a row or column, this would allow the patterns to be shifted.
uint16_t getNeoPixel(uint16_t row, uint16_t column, uint16_t shiftRow, uint16_t shiftColumn)
{
  return COLUMNS * ((row + shiftRow) % ROWS) + (column + shiftColumn) % COLUMNS;
}

uint16_t getNeoPixel(uint16_t row, uint16_t column)
{
  return getNeoPixel(row, column, 0, 0);
}

uint16_t getNeoPixelMirrorVertical(uint16_t row, uint16_t column, uint16_t shiftRow, uint16_t shiftColumn)
{
  uint16_t mirror_column = COLUMNS - column - 1;
  return getNeoPixel(row, mirror_column, shiftRow, shiftColumn);
}

uint16_t getNeoPixelMirrorHorizontal(uint16_t row, uint16_t column, uint16_t shiftRow, uint16_t shiftColumn)
{
  uint16_t mirror_row = ROWS - row - 1;
  return getNeoPixel(mirror_row, column, shiftRow, shiftColumn);
}

void setNeoPixelColor(uint16_t row, uint16_t column, uint32_t c, uint16_t wait)
{
  strip.setPixelColor(getNeoPixel(row,column), c);
  strip.show();
  delay(wait);
}

void setPixelColorPattern(uint16_t pattern[ROWS][COLUMNS], uint16_t shiftRow, uint16_t shiftColumn, uint32_t colors[], size_t lenOfColors, uint16_t wait)
{
  for (uint16_t row = 0; row < ROWS; row++)
  {
    for (uint16_t col = 0; col < COLUMNS; col++)
    {
      if(lenOfColors <= pattern[row][col]  || 0 > pattern[row][col])
      {
        strip.setPixelColor(getNeoPixel(row, col, shiftRow, shiftColumn), strip.Color(0, 0, 0));
        continue;
      }
      strip.setPixelColor(getNeoPixel(row, col, shiftRow, shiftColumn), colors[pattern[row][col]]);
    }

  }
  strip.show();
  delay(wait);
}


void setPixelColorPattern(uint16_t pattern[ROWS][COLUMNS], uint32_t colors[], size_t lenOfColors, uint16_t wait)
{
  setPixelColorPattern(pattern, 0,0, colors, lenOfColors, wait);
}

void setPixelColorPatternMirrorVertical(uint16_t pattern[ROWS][COLUMNS], uint16_t shiftRow, uint16_t shiftColumn, uint32_t colors[], size_t lenOfColors, uint16_t wait)
{
  for (uint16_t row = 0; row < ROWS; row++)
  {
    for (uint16_t col = 0; col < COLUMNS; col++)
    {
      if(lenOfColors <= pattern[row][col]  || 0 > pattern[row][col])
      {
        strip.setPixelColor(getNeoPixelMirrorVertical(row, col, shiftRow, shiftColumn), strip.Color(0, 0, 0));
        continue;
      }
      strip.setPixelColor(getNeoPixelMirrorVertical(row, col, shiftRow, shiftColumn), colors[pattern[row][col]]);
    }

  }
  strip.show();
  delay(wait);
}

void setPixelColorPatternMirrorHorizontal(uint16_t pattern[ROWS][COLUMNS], uint16_t shiftRow, uint16_t shiftColumn, uint32_t colors[], size_t lenOfColors, uint16_t wait)
{
  for (uint16_t row = 0; row < ROWS; row++)
  {
    for (uint16_t col = 0; col < COLUMNS; col++)
    {
      if(lenOfColors <= pattern[row][col]  || 0 > pattern[row][col])
      {
        strip.setPixelColor(getNeoPixelMirrorHorizontal(row, col, shiftRow, shiftColumn), strip.Color(0, 0, 0));
        continue;
      }
      strip.setPixelColor(getNeoPixelMirrorHorizontal(row, col, shiftRow, shiftColumn), colors[pattern[row][col]]);
    }

  }
  strip.show();
  delay(wait);
}