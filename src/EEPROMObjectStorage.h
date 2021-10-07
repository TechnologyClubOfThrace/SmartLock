#include <Arduino.h>
#include <String.h>
#include <Storage.h>
#include <map>

enum TagCategory 
{
    User,
    Unknown,
    Master
};

class EEPROMObjectStorage :  public Storage 
{     
    public: 
        EEPROMObjectStorage();
        bool IsMasterTag(String TagID);
        bool IsUserTag(String TagID);
        void AddTagToKnownUserTagsList(String TagID);     
        void RemoveTagFromUserTagsList(String TagID); 

    private:
        std::map<String,TagCategory> tagsList;
        std::map<String,TagCategory>::iterator it;
        void initializeTagsList();

};

