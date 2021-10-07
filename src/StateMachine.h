// Accepts RFID tag IDs of byte[10]
// Implements 
//      access control rules 
//      TagID bytes formating to string 
//      TagID lookup
// agnostic to underlying storage method and card reader class

#include <Arduino.h>
#include <String.h>
#include <EEPROMObjectStorage.h>
#include <TheLock.h> 

const int ID_LENGTH = 10;

enum state 
{  
    Waiting, 
    UserTagScanned, 
    UnknownTagScanned, 
    MasterTagScanned, 
} ;

class StateMachine 
{
    private:
        state previousState;
        TagCategory currentScannedTagCategory;
        String tag_ID_as_byte_array;
        EEPROMObjectStorage storage;
        TheLock lock;

        void AllowAccess();     
        void DenyAccess();
        void AddTagToAllowedList(String TagID);
        void RemoveTagFromAllowedList(String TagID);
        String GetTagIDAsString(byte tag_ID_as_byte_array[ID_LENGTH]);

    public: 
        state currentState;
        StateMachine();
        void ProcessNewScannedTag(byte tag_ID_as_byte_array[ID_LENGTH]);
        TagCategory LookupTag(String TagID);
};