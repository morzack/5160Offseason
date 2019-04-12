// script to handle an arduino LED strip using this protocol thing

// incoming format is "r,g,b,a"

#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 39
#define BIRGHTNESS 100

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB+NEO_KHZ800);

void setup() {
    Serial.begin(9600);
    strip.begin();
    strip.show();
    strip.setBrightness(100);
}

void setColor(uint32_t color) {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void loop() {
    String strRead;
    while (Serial.available()) {
        strRead = Serial.readString();
    }

    if (strRead.length()>0) {
        Serial.println(strRead);
        // 000,000,000,000
        // 0123456789
        int r = strRead.substring(0, 3).toInt();
        int g = strRead.substring(4, 7).toInt();
        int b = strRead.substring(8, 11).toInt();
        int a = strRead.substring(12, 15).toInt();
        Serial.println(String(r) + String(g) + String(b) + String(a));
        setColor(strip.Color(r, g, b));
        delay(500);
    }
}
