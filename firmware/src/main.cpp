#include <Arduino.h>
#include <FastLED.h>
#include <LiquidCrystal.h>

#define LED_PIN 4
#define LED_COUNT 4

const byte d4 = 7, d5 = 16, d6 = 18, d7 = 17, e1 = 15, e2 = 6, rs = 5;

CRGB leds[LED_COUNT];

void setup() {
    // initLcd();
    Serial.begin(115200);
    LiquidCrystal lcdTop = LiquidCrystal(rs, e1, d4, d5, d6, d7);
    LiquidCrystal lcdBot = LiquidCrystal(rs, e2, d4, d5, d6, d7);
    lcdTop.begin(40, 2);
    lcdBot.begin(40, 2);

    FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, LED_COUNT);
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
    leds[2] = CRGB::Red;
    leds[3] = CRGB::Red;
    FastLED.show();

    // lcdTop.print("ABCD");
    // lcdTop.write(0xFF);
    lcdTop.setCursor(10, 0);
    lcdTop.print("hell world");
    lcdBot.setCursor(0, 0);
    lcdBot.print("hell world");
}

void loop() { delay(1000); }
