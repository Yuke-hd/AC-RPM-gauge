#include <Adafruit_NeoPixel.h>

// constants won't change. They're used here to
// set pin numbers:
const int ledPin = 3;    
const int numLeds = 16; // the number of the neopixel strip
const int delta = 256 / numLeds;
int lastNum = 0;
const int fps = 16;
int recievedChar;
int rpm=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.setBrightness(20); // 1/3 brightness
  Serial.begin(115200);

}

void loop() {
  rpm = Serial.read();
  turnon(rpm);
}

void turnon(int rpm) {
  if (rpm < 0) {
    return;
  }
  if (rpm > numLeds) {
    return;
  }
  if (rpm < lastNum) {
    for (int x = strip.numPixels() - 1; x >= 0 ; x--) {
      if (x < rpm) {
        strip.setPixelColor(x, getColor(x));
      }else {
        strip.setPixelColor(x, 0);
      }
      strip.show();
    }
  } else {
    for (int x = 0; x < strip.numPixels(); x++) {
      if (x < rpm) {
        strip.setPixelColor(x, getColor(x));
      }else {
        strip.setPixelColor(x, 0);
      }
      strip.show();
    }
  }
  lastNum = rpm;
}

uint32_t getColor(int ledPos){
  if(ledPos < 11){
    return strip.Color(0, 255, 0); // green
  }else if(ledPos >= 11 && ledPos <= 13){
    return strip.Color(0, 0, 255); // red
  }else{
    return strip.Color(255, 0, 0); 
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
