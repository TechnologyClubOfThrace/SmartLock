#include <Arduino.h>
#include <string>
#include "TheLock.h"
#include "Portal.h"

extern void cardReadSetup();
extern void cardReadLoop();

TheLock lock;

void setup() {
  Serial.begin(115200);		

  pinMode(LED_BUILTIN, OUTPUT);

  lock.Init();

  portalSetup();

  cardReadSetup();
}

int count = 0;

void loop() {
  portalLoop();

  cardReadLoop();
}


