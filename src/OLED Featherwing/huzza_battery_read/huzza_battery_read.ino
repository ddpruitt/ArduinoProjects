// Adafruit OLED FeatherWing Battery Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>


Adafruit_FeatherOLED oled = Adafruit_FeatherOLED();

// integer variable to hold current counter value
int count = 0;

void setup()
{
  Serial.begin(115200);

  oled.init();
  oled.setBatteryVisible(true);
}

void loop()
{
  battery_level();
  
  // clear the current count
  oled.clearDisplay();

  // get the current voltage of the battery from
  // one of the platform specific functions below
  float battery = getBatteryVoltageByDividers();

  // update the battery icon
  oled.setBattery(battery);
  oled.renderBattery();

  // print the count value to the OLED
  oled.print("count: ");
  oled.println(count);

  // update the display with the new count
  oled.display();

  // increment the counter by 1
  count++;

  // delay 1 second (1 second == 1000 milliseconds)
  delay(60000);

}


float getBatteryVoltageByDividers() {
  // read the battery level from the ESP8266 analog in pin.
  // analog read level is 10 bit 0-1023 (0V-1V).
  // our 10K & (3)*560 voltage divider takes the max
  // lipo value of 4.2V and drops it to 0.758V max.
  // this means our min analog read value should be 450 (3.14V)
  // and the max analog read value should be 600 (4.2V).
    float measuredvbat = analogRead(A0);
    float r1 = 10000;
    float r2 = 3.0 * 560;
    
    float calculatedV = (measuredvbat/1024) * (r1 + r2) / r2;
    return calculatedV;

  }


