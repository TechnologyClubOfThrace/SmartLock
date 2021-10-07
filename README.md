# SmartLock
Smart Lock using ESP32

The sketch consists of 3 modules:
## The StateMachine 
deals with all the access logic as shown in the state diagram below.

## The EEPROMObjectStorage 
takes care of saving and updating the list of allowed users.  
Any class that inherits from the Storage abstract class can be used instead. e.g. we can create  
* an SD_Storage class to store users in SD card or  
* a online_Storage class to store users on a DB somewhere online

## TheLock
implements the interface to the actual lock hardware (stepper motor)

