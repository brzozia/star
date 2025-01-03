#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <Arduino.h>
#include <FastLED.h>

#define LEDS_NUM_1 28
#define LEDS_NUM_2 60
#define LEDS_NUM LEDS_NUM_1 + LEDS_NUM_2
#define TAIL_LEN 26
#define PIN_NO 7

class LEDStrip17
{
public:
    CRGB leds[LEDS_NUM];

    LEDStrip17()
    {
        // Initialize the LED array
        // FastLED.addLeds<WS2812B, PIN_NO, GRB>(leds, LEDS_NUM_GRB);
        FastLED.addLeds<WS2812B, PIN_NO, GRB>(leds, LEDS_NUM).setCorrection(Candle);
    }

    void begin()
    {
        FastLED.setBrightness(brightness);
        clear(); // Clear the strip on initialization
    }

    void setBrightness(int b)
    {
        brightness = constrain(b, 0, 255);
        FastLED.setBrightness(brightness);
    }

    void clear()
    {
        fill_solid(leds, LEDS_NUM, CRGB::Black);
        FastLED.show();
    }

    void setColor(int index, const CRGB &color)
    {
        if (index >= 0 && index < LEDS_NUM_1)
        {
            leds[index] = color;
        }
        if (index >= LEDS_NUM_1 && index < LEDS_NUM)
        {
            leds[index] = calcColorForLeds2(color);
        }
    }

    void fillColor(const CRGB &color)
    {
        for (int i = 0; i < LEDS_NUM_1; i++)
        {
            leds[i] = color;
        }
        for (int i = LEDS_NUM_1; i < LEDS_NUM; i++)
        {
            leds[i] = calcColorForLeds2(color);
        }
        // fill_solid(leds, LEDS_NUM, color);
    }

    CRGB calcColorForLeds2(CRGB color)
    {
        return CRGB(color.r - 170, color.g, color.b);
    }

    void show()
    {
        FastLED.show();
    }

    void lightOneAfterOne(const CRGB &color, int delayTime)
    {
        for (int i = 0; i < LEDS_NUM; i++)
        {
            setColor(i, color);
            show();
            delay(delayTime);
        }
    }

    void lightOneAfterOneTail(const CRGB &color, int delayTime)
    {
        for (int i = 0; i < TAIL_LEN; i++)
        {
            setColor(i, color);
            show();
            delay(delayTime);
        }
    }

    void clearOneAfterOne(int delayTime)
    {
        for (int i = 0; i < LEDS_NUM; i++)
        {
            leds[i] = CRGB::Black;
            show();
            delay(delayTime);
        }
    }

    void lightOneByOne(const CRGB &color, int delayTime)
    {
        for (int i = 0; i < LEDS_NUM; i++)
        {
            setColor(i, color);
            show();
            delay(delayTime);
            leds[i] = CRGB::Black;
        }
    }

    void blinkAll(const CRGB &color, int delayTime)
    {
        fillColor(color);
        show();
        delay(delayTime);
        clear();
        delay(delayTime);
    }

    void blinkStar(const CRGB &color, int delayTime)
    {
        for (int i = TAIL_LEN; i < LEDS_NUM; i++)
        {
            setColor(i, color);
        }
        show();
        delay(delayTime);
        clear();
        delay(delayTime);
    }

    void blinkEveryN(const CRGB &color, int delayTime, int n, int from)
    {
        for (int i = from; i < LEDS_NUM; i+=n)
        {
            setColor(i, color);
        }
        show();
        delay(delayTime);
        clear();
        delay(delayTime);
    }

private:
    int brightness = 255;
};

#endif // LEDSTRIP_H