#include <Arduino.h>
#include <FastLED.h>
#include <RH_ASK.h>
#include <SPI.h>
#include "LedStrip/LedStrip.cpp"

// put function declarations here:
#define SEQUENCES_COUNT 5
#define DEFAULT_COLOR CRGB(255, 90, 0)

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
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  while (1)
  {
    delay(5);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      Serial.print("Message: ");
      uint8_t msg = buf[0];
      Serial.println(msg);
      if (msg == 1)
      {
        i = (i + 1) % SEQUENCES_COUNT;
        lightOn(i);
      }
    }
  }
}

// put function definitions here:
void lightOn(int seq)
{
  if (seq == 1)
  {
    for (int t = 0; t < 3; t++)
    {
      led_strip17.lightOneAfterOne(DEFAULT_COLOR, 20);
      led_strip17.clearOneAfterOne(20);
    }
  }
  else if (seq == 2)
  {
    for (int t = 0; t < 3; t++)
    {
      led_strip17.lightOneByOne(DEFAULT_COLOR, 30);
    }
    led_strip17.blinkStar(DEFAULT_COLOR, 300);
  }
  else if (seq == 3)
  {
    for (int i = 0; i < 5; i++)
    {
      led_strip17.blinkAll(DEFAULT_COLOR, 300);
    }
  }
  else if(seq == 4){
    led_strip17.lightOneAfterOneTail(DEFAULT_COLOR, 60);
    for (int i = 0; i < 3; i++)
    {
      led_strip17.blinkStar(DEFAULT_COLOR, 500);
    }
  }
  else if(seq == 0){
    for(int i=0;i<2;i++){
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 3, 0);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 7, 1);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 5, 2);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 3, 1);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 4, 0);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 7, 5);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 5, 2);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 3, 1);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 6, 2);
    led_strip17.blinkEveryN(DEFAULT_COLOR, 100, 2, 1);
    }
  }
}