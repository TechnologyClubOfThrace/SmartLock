#include <TheLock.h>


TheLock::TheLock()
{
    steps = 200;
}

void TheLock::Init()
{
    //lock initialization code

    // Setup stepper motor
    stepper.setEnablePin(ENABLE_DRV8825_PIN);
    stepper.setPinsInverted(false, false, true);

    // Set the maximum speed in steps per second:
    stepper.setMaxSpeed(500);


    Serial.println("Lock initialized");

    stepper.setCurrentPosition(0);


    stepper.disableOutputs();
}

void TheLock::SetSteps(int value)
{
    if (steps > 0)
    {
        steps = value;
    }
}

void TheLock::Unlock()
{
    // code to turn the key to unlock
    Move(-steps, -200);
}

void TheLock::Lock()
{
    // code to turn the key to lock
    Move(steps, 200);
}

void TheLock::Move(int steps, int speed)
{
    stepper.enableOutputs();

   // Set the current position to 0:
    stepper.setCurrentPosition(0);
    // Run the motor forward at 200 steps/second until the motor reaches 400 steps (2 revolutions):
    while(stepper.currentPosition() != steps)
    {
        stepper.setSpeed(speed);
        stepper.runSpeed();
    }

    stepper.disableOutputs();
}