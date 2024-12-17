#include <Arduino.h>
#include <FastLED.h>
#include <RH_ASK.h>
#include <SPI.h>
#include "LedStrip/LedStrip.cpp"

// put function declarations here:
#define SHOW_DURATION_SEC 3

uint8_t LIGHT_ON = 0;
LEDStrip17 led_strip17 = LEDStrip17();
RH_ASK driver(2000, 14, 16, 10);
void lightOn(int);

void setup()
{
  Serial.begin(9600);
  led_strip17.begin();
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  delay(100);
  int i = 1;
  uint8_t buf[5];
  uint8_t buflen = sizeof(buf);
  unsigned long start = 0;

  while (1)
  {
    delay(10);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      Serial.print("Message: ");
      char *msg = (char *)buf;
      Serial.print(msg);
      if (msg)
      {
        lightOn(i += 23);
        start = millis();
      }
    }
    // if (LIGHT_ON && (start + (SHOW_DURATION_SEC * 1000) < millis()))
    // {
    //   Serial.println("czyszcze");
    //   led_strip17.clear();
    //   LIGHT_ON = 0;
    // }
  }
}

// put function definitions here:
void lightOn(int i)
{
  LIGHT_ON = 1;
  // led_strip17.fillColor(CRGB(i % 256, 100, 100));
  // led_strip17.show();
  for(int t=0;t<1;t++){
    led_strip17.oneByOne(CRGB::AntiqueWhite, 30);
    led_strip17.clear();
  }
}