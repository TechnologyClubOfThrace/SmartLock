#include <string>
#include <StateMachine.h>

StateMachine::StateMachine()
{
    currentState = Waiting;
    //LocalStorage storage;

}

void StateMachine::AllowAccess()
{
    Serial.println("Access allowed.");
    lock.Unlock(); // +probably wait 5 secs and relock
};

void StateMachine::DenyAccess()
{
    Serial.println("Access Denied.");
    // possibly log also
};

void StateMachine::AddTagToAllowedList(String TagID)
{
    storage.AddTagToKnownUserTagsList(TagID);
    Serial.println("Tag added to known user tags.");
};

void StateMachine::RemoveTagFromAllowedList(String TagID)
{
    storage.RemoveTagFromUserTagsList(TagID);
    Serial.println("Tag removed from known user tags.");
};

void StateMachine::ProcessNewScannedTag(byte tag_ID_as_byte_array[ID_LENGTH])
{
    String TagID;
    TagID = GetTagIDAsString(tag_ID_as_byte_array);
    //String TagID = "1234";
    Serial.print("TagID: ");
    Serial.println(TagID);
    return ;
    currentScannedTagCategory = LookupTag(TagID);

    if (previousState==Waiting)
    {
        switch (currentScannedTagCategory)
        {
        case User:
            AllowAccess();
            break;
        case Unknown:
            DenyAccess();
            break;
        case Master:
            previousState = MasterTagScanned;
            break;
        default:
            break;
        }  
    }

    if (previousState==MasterTagScanned)
    {
        switch (currentScannedTagCategory)
        {
        case User:
            RemoveTagFromAllowedList(TagID);
            break;
        case Unknown:
            AddTagToAllowedList(TagID);
            break;
        case Master:
            previousState = Waiting;
            break;
        default:
            break;
        }
    }

    return;
}

TagCategory StateMachine::LookupTag(String TagID)
{
    if (storage.IsMasterTag(TagID))
    {
        return Master;
    }
    else if (storage.IsUserTag(TagID))
    {
        return User;
    }
    else
    {
        return Unknown;
    }
}  

String StateMachine::GetTagIDAsString(byte tag_ID_as_byte_array[ID_LENGTH])
{
  char tag[41]{};  

  for (int b = 0; b < ID_LENGTH; b++) 
  {
    char buff[4]{}; 
    snprintf(buff, 4, "%3.0d", tag_ID_as_byte_array[b]);
    strncat(tag, buff, 3);
    strncat(tag,"-",1);
  };

  return tag;
}
