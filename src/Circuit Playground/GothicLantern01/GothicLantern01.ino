#include <Adafruit_CircuitPlayground.h>

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

int brightness = 254;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
}

void loop() {

  CircuitPlayground.clearPixels();
  CircuitPlayground.setBrightness(brightness);
  for(int led=0; led <10; led++){
    CircuitPlayground.setPixelColor(led, 0xFF0000);
  }
  delay(100);
  
  for(int red=0; red<=255; red+=5) {
    for(int green=0; green<=255; green+=5){
      for(int blue=0; blue <=255; blue+=5){
        CircuitPlayground.clearPixels();
        for(int led=0; led <10; led++){
          CircuitPlayground.setPixelColor(led, red, green, blue);
        }
          delay(100);
      }
    }
  }
}
