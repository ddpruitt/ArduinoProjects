#include <NeoPixelMatrix.h>

#define SPEED 100 //faster the lower the number

uint16_t pattern00[ROWS][COLUMNS] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

uint16_t pattern01[ROWS][COLUMNS] =
    {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
    };

uint16_t pattern02[ROWS][COLUMNS] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

uint16_t pattern03[ROWS][COLUMNS] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0}
    };

uint16_t pattern03a[ROWS][COLUMNS] =
    {
        {1, 2, 2, 2, 2, 2, 2, 2},
        {1, 3, 3, 3, 3, 3, 3, 3},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0}
    };

uint16_t pattern04[ROWS][COLUMNS] =
    {
        {1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 1}
    };

uint16_t pattern05[ROWS][COLUMNS] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

uint16_t pattern06[ROWS][COLUMNS] =
    {
        {0, 0, 0, 0, 4, 3, 2, 1},
        {0, 0, 0, 4, 3, 2, 1, 0},
        {0, 0, 4, 3, 2, 1, 0, 0},
        {0, 4, 3, 2, 1, 0, 0, 0}
    };

uint16_t pattern07[ROWS][COLUMNS] =
    {
        {1, 2, 3, 4, 0, 0, 0, 0},
        {1, 2, 3, 4, 0, 0, 0, 0},
        {1, 2, 3, 4, 0, 0, 0, 0},
        {1, 2, 3, 4, 0, 0, 0, 0},
    };


void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{

  setPixelColorPattern(pattern07, 0, 0, cRGBW, 5, 3*SPEED);
  setPixelColorPatternMirrorVertical(pattern07, 0, 0, cRGBW, 5, 3*SPEED);

  // for (size_t i = 0; i < COLUMNS; i++)
  // {
  //   setPixelColorPattern(pattern01, 0, i, greenColors, 2, SPEED);
  // }

  // for (size_t i = COLUMNS; i > 0; i--)
  // {
  //   setPixelColorPattern(pattern01, 0, i - 1, greenColors, 2, SPEED);
  // }

  // for (size_t i = 0; i < ROWS; i++)
  // {
  //   setPixelColorPattern(pattern02, i, 0, blueColors, 2, SPEED);
  // }

  // for (size_t i = ROWS; i > 0; i--)
  // {
  //   setPixelColorPattern(pattern02, i - 1, 0, blueColors, 2, SPEED);
  // }

  // for (size_t i = 0; i < COLUMNS; i++)
  // {
  //   for (size_t j = 0; j < ROWS; j++)
  //   {
  //     setPixelColorPattern(pattern03a, j, i, cRGBW, 5, SPEED);
  //   }
  // }

  // for (size_t i = 0; i < (10 * COLUMNS); i++)
  // {
  //   setPixelColorPattern(pattern06, 0, -i, cRGBW, 5, SPEED);
  // }

  // setPixelColorPattern(pattern02, cRGBW, 5, SPEED);

  // setPixelColorPattern(pattern03, blueColors, 2, SPEED);
  // setPixelColorPattern(pattern04, redColors, 2, SPEED);
  // setPixelColorPattern(pattern05, greenColors, 2, SPEED);

  // setPixelColorPattern(pattern05, 0, 0, redBlueColors, 2, SPEED);
  // setPixelColorPattern(pattern05, 1, 0, redBlueColors, 2, SPEED);

}