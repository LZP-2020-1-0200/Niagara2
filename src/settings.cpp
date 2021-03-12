#include "settings.h"

#include "LittleFS.h"
#include "buffers.h"
Settings settings;

Settings::Settings(/* args */)
{
}

void Settings::load(void)
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
        }
    }
    else
        Serial.println(F("LittleFS failed"));
}
Settings::~Settings()
{
}
