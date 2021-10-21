#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#ifndef NEWPIXELMATRIX_INCLUDED
#define NEWPIXELMATRIX_INCLUDED

#define PIN 6     // Pin for data
#define LEDS 32   // How many LEDs?
#define ROWS 4    // count LEDs downward
#define COLUMNS 8 //Count your LEDS to the right

extern Adafruit_NeoPixel strip;

extern uint32_t c000 ;
extern uint32_t cRed;
extern uint32_t cGreen;
extern uint32_t cBlue;
extern uint32_t cWhite;

extern uint32_t cRGBW[5];

extern uint32_t redColors[2];
extern uint32_t blueColors[2];
extern uint32_t greenColors[2];
extern uint32_t whiteColors[2];

extern uint32_t redBlueColors[2];
extern uint32_t blueRedColors[2];


uint16_t getNeoPixel(uint16_t row, uint16_t column, uint16_t shiftRow, uint16_t shiftColumn);
uint16_t getNeoPixel(uint16_t row, uint16_t column);

void setNeoPixelColor(uint16_t row, uint16_t column, uint32_t c, uint16_t wait);

void setPixelColorPattern(uint16_t pattern[ROWS][COLUMNS], uint16_t shiftRow, uint16_t shiftColumn, uint32_t colors[], size_t lenOfColors, uint16_t wait);
void setPixelColorPattern(uint16_t pattern[ROWS][COLUMNS], uint32_t colors[], size_t lenOfColors, uint16_t wait);

void setPixelColorPatternMirrorVertical(uint16_t pattern[ROWS][COLUMNS], uint16_t shiftRow, uint16_t shiftColumn, uint32_t colors[], size_t lenOfColors, uint16_t wait);
void setPixelColorPatternMirrorHorizontal(uint16_t pattern[ROWS][COLUMNS], uint16_t shiftRow, uint16_t shiftColumn, uint32_t colors[], size_t lenOfColors, uint16_t wait);

#endif // NEWPIXELMATRIX_INCLUDED
