#include <Arduino.h>
#include <U8glib.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN 12

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The complete list of supported devices is here: http://code.google.com/p/u8glib/wiki/device

U8GLIB_NHD_C12864 u8g(13, 11, 10, 9, 8); // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, RST = 8

#define MENU_ITEMS 6

void setupLcd(void)
{
  u8g.setFont(u8g_font_6x12); //4x6 5x7 5x8 6x10 6x12 6x13
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();

  u8g.setContrast(0);
}

void readDhtSensors(void)
{

  // READ DATA
  //u8g
  //u8g.println("DHT11, ");

  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
  case DHTLIB_OK:
    u8g.println("OK, ");
    break;
  case DHTLIB_ERROR_CHECKSUM:
    u8g.println("Checksum error, ");
    break;
  case DHTLIB_ERROR_TIMEOUT:
    u8g.println("Time out error, ");
    break;
  case DHTLIB_ERROR_CONNECT:
    u8g.println("Connect error, ");
    break;
  case DHTLIB_ERROR_ACK_L:
    u8g.println("Ack Low error, ");
    break;
  case DHTLIB_ERROR_ACK_H:
    u8g.println("Ack High error, ");
    break;
  default:
    u8g.println("Unknown error, ");
    break;
  }
  // DISPLAY DATA
  u8g.println(DHT.humidity, 1);
  u8g.println(DHT.temperature, 1);

  delay(500);
}
void setup()
{
  u8g.setRot180(); // rotate screen, if required
  //Serial.begin(115200);
}

void loop()
{
  u8g.firstPage();
  do
  {
    readDhtSensors();
  } while (u8g.nextPage());
}
