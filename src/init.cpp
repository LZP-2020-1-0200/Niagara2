#include "init.h"
#include "LittleFS.h"

#include "buffers.h"

void initialization_report(const __FlashStringHelper *msg)
{

  static bool init_complete = false;
  if (!init_complete)
  {
    Serial.begin(DEFAULT_BAUD);

    if (LittleFS.begin())
    {
      File f = LittleFS.open("/banner.txt", "r");
      if (!f)
      {
        Serial.println(F("banner.txt file open failed"));
      }
      else
      {
        int n = 0;
        do
        {
          n = f.readBytes(tmp.buf(), tmp.len);
          Serial.write(tmp.buf(), n);
        } while (n == tmp.len);
        f.close();
        init_complete = true;
      }
    }
    else
      Serial.println(F("LittleFS failed"));
  }
  Serial.println(msg);
}