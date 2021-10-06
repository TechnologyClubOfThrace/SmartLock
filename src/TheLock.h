#include <Arduino.h>
#include <AccelStepper.h>


// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define DIR_PIN 2
#define STEP_PIN 3
#define motorInterfaceType 1

// Pin to control enabling the DRV8825 driver. Connect this to ENABLE pin
#define ENABLE_DRV8825_PIN 4


class TheLock
{     
    public: 
        TheLock();
        void Lock();
        void Unlock();

    private:
        // Create a new instance of the AccelStepper class:
        AccelStepper stepper = AccelStepper(motorInterfaceType, STEP_PIN, DIR_PIN);

};