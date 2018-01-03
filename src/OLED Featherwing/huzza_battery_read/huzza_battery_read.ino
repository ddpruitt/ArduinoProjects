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

#define VBATPIN A9

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
  float battery = getBatteryVoltage();

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

  // esp8266 feather
  #define VBATPIN A0

  float getBatteryVoltage() {

    float measuredvbat = analogRead(A0);

    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage

    return measuredvbat;

  }

void battery_level() {
 
  // read the battery level from the ESP8266 analog in pin.
  // analog read level is 10 bit 0-1023 (0V-1V).
  // our 1M & 220K voltage divider takes the max
  // lipo value of 4.2V and drops it to 0.758V max.
  // this means our min analog read value should be 580 (3.14V)
  // and the max analog read value should be 774 (4.2V).
  int measuredLevel = analogRead(A0);
  
  // convert battery level to percent
  int level = map(measuredLevel, 450, 620, 0, 100);
  Serial.print("Battery level: ("); Serial.print(measuredLevel); Serial.print(") ");Serial.print(level); Serial.println("%");
}


