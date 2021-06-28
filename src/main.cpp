#include <Arduino.h>

// Include the AccelStepper library:
#include <AccelStepper.h>

#ifndef LED_BUILTIN 
#define LED_BUILTIN 13
#endif

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define DIR_PIN 2
#define STEP_PIN 3
#define motorInterfaceType 1

// Pin to control enabling the DRV8825 driver. Connect this to ENABLE pin
#define ENABLE_DRV8825_PIN 4

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, STEP_PIN, DIR_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  // Setup stepper motor
  stepper.setEnablePin(ENABLE_DRV8825_PIN);

  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(100);

  stepper.disableOutputs();
}

void loop() {
  // put your main code here, to run repeatedly:

  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("ON");
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  Serial.println("OFF");
  delay(1000);
}
