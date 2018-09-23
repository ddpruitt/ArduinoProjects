#include <Adafruit_CircuitPlayground.h>

/*
uint32_t neoPixelColors[10] = {
  0xFF0000,
  0xFF8000,
  0xFFFF00,
  0x80FF00,
  0x00FF00,
  0x00FF40,
  0x00FF80,
  0x00FFFF,
  0x0080FF,
  0x0000FF 
};
*/
/*
 uint32_t neoPixelColors[10] = {
  0xFF0000,
  0x808000,
  0x00FF00,
  0x008080,
  0x0000FF,
  0xFF0000,
  0x808000,
  0x00FF00,
  0x008080,
  0x0000FF
};
*/

uint32_t neoPixelColors[10] = {
  0xFF0000,
  0x808000,
  0x00FF00,
  0x008080,
  0x0000FF,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000
};

int brightness = 20;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
}

void loop() {

  uint32_t tmp = neoPixelColors[0];
  for(int i=1; i<=9; i++){
    neoPixelColors[i-1] = neoPixelColors[i];
  }
  neoPixelColors[9] = tmp;
 
  for(int i=0; i<=9;i++){
    //Serial.println(neoPixelColors[i]);
    CircuitPlayground.setPixelColor(i, neoPixelColors[i]);
    CircuitPlayground.setBrightness(brightness);
  }
  
  delay(100);
}
