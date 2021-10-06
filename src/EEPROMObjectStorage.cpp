#include <Arduino.h>
#include <EEPROM.h> 
#include <EEPROMObjectStorage.h>

EEPROMObjectStorage::EEPROMObjectStorage()
{
    EEPROM.get(0, tagsList);

    String masterCardID = "1234";

    it = tagsList.find(masterCardID);

    if (it != tagsList.end()) //if EEPROM contains no tagsList
    {
        tagsList[masterCardID]=Master;  //initialize it with a master tag
        EEPROM.put(0,tagsList);         //and save it to EEPROM
    }
}

bool EEPROMObjectStorage::IsMasterTag(String tagIDToFind)
{
    it = tagsList.find(tagIDToFind);
    if (tagsList.at(tagIDToFind) == Master )
    {
        return true;
    }
    return false;
}

bool EEPROMObjectStorage::IsUserTag(String tagIDToFind)
{
    it = tagsList.find(tagIDToFind);
    if (tagsList.at(tagIDToFind) == User )
    {
        return true;
    }
    return false;
}

void EEPROMObjectStorage::AddTagToKnownUserTagsList(String tagIDtoWrite)
{
    tagsList[tagIDtoWrite] = User;
    EEPROM.put(0,tagsList);
}


void EEPROMObjectStorage::RemoveTagFromUserTagsList(String tagIDtoRemove)
{
    tagsList.erase(tagIDtoRemove);
    EEPROM.put(0,tagsList);
}

