#include "init.h"
#include "LittleFS.h"

void initialization_report(const __FlashStringHelper *msg)
{ // call this function from class constructors,
  // and other initializers
  // to see when they execute
  static bool init_complete = false;
  if (!init_complete)
  {
    Serial.begin(DEFAULT_BAUD);
    if (LittleFS.begin())
    {
      Serial.println(F("LittleFS initialized"));
      File f = LittleFS.open("/tesp.txt", "r");
      String read_ = f.readString();
      Serial.println(read_);
    }

    else
      Serial.println(F("LittleFS failed"));
    init_complete = true;
  }
  Serial.println(msg);
}