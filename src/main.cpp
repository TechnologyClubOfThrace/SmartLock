#include <Arduino.h>
#include <string>


extern void portalSetup();
extern void portalLoop();

extern void cardReadSetup();
extern void cardReadLoop();

void setup() {
  Serial.begin(115200);		

  portalSetup();

  cardReadSetup();
}

void loop() {
  portalLoop();

  cardReadLoop();
}


