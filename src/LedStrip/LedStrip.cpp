#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <Arduino.h>
#include <FastLED.h>


#define LEDS_NUM 28
#define PIN_NO 7

class LEDStrip17 {
public:
    CRGB leds[LEDS_NUM];
    
    LEDStrip17() {
        // Initialize the LED array
        FastLED.addLeds<WS2812B, PIN_NO, GRB>(leds, LEDS_NUM);
    }

    void begin() {
        FastLED.setBrightness(brightness);
        clear(); // Clear the strip on initialization
    }

    void setBrightness(int b) {
        brightness = constrain(b, 0, 255);
        FastLED.setBrightness(brightness);
    }

    void clear() {
        fill_solid(leds, LEDS_NUM, CRGB::Black);
        FastLED.show();
    }

    void setColor(int index, const CRGB& color) {
        if (index >= 0 && index < LEDS_NUM) {
            leds[index] = color;
        }
    }

    void fillColor(const CRGB& color) {
        fill_solid(leds, LEDS_NUM, color);
    }

    void show() {
        FastLED.show();
    }

    void oneByOne(const CRGB& color, int delayTime){
        for(int i=0;i<LEDS_NUM;i++){
            leds[i] = color;
            show();
            delay(delayTime);
        }
    }

private:
    int brightness = 255;
};


#endif // LEDSTRIP_H