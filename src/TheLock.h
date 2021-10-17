#include <Arduino.h>
#include <AccelStepper.h>


// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define DIR_PIN 12
#define STEP_PIN 14
#define motorInterfaceType 1

// Pin to control enabling the DRV8825 driver. Connect this to ENABLE pin
#define ENABLE_DRV8825_PIN 27

#ifndef LED_BUILTIN 
#define LED_BUILTIN 13
#endif

class TheLock
{     
    public: 
        TheLock();

        void Init();
        void Lock();
        void Unlock();

        void SetSteps(int steps);

    private:
        // Create a new instance of the AccelStepper class:
        AccelStepper stepper = AccelStepper(motorInterfaceType, STEP_PIN, DIR_PIN);

        void Move(int steps, int speed);

        int steps;
};