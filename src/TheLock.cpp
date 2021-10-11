#include <TheLock.h>

#ifndef LED_BUILTIN 
#define LED_BUILTIN 13
#endif

TheLock::TheLock()
{
    //lock initialization code
    pinMode(LED_BUILTIN, OUTPUT);

    // Setup stepper motor
    stepper.setEnablePin(ENABLE_DRV8825_PIN);

    // Set the maximum speed in steps per second:
    stepper.setMaxSpeed(100);

    stepper.disableOutputs();
}

void TheLock::Unlock()
{
    // code to turn the key to unlock
    // e.g. stepper.moveTo(1);
}

void TheLock::Lock()
{
    // code to turn the key to lock
}