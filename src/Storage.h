// Interface (abstract class) for storing Tags
// You can define classes that inherit (implement) it for
// e.g. EEPROM raw storage, EEPROM object storage, SD cart, online authDB

#include <Arduino.h>

class Storage 
{     
    public: 
        bool virtual IsMasterTag(String TagID);
        bool virtual IsUserTag(String TagID);
        void virtual AddTagToKnownUserTagsList(String TagID);     
        void virtual RemoveTagFromUserTagsList(String TagID);   
};