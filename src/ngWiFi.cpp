#include "ngWiFi.h"

#include <ESP8266WiFi.h>

NG_WiFi::NG_WiFi(/* args */) // : NG_Task(0, 1000000)
{
    // Serial.println(F("initializing NG_WiFi"));
    //  WiFi.begin("Optika", "slepens123");
}

NG_WiFi::~NG_WiFi()
{
}

int NG_WiFi::exec(const uint32 &new_u)
{
    //   int upd = NG_Task::exec(new_u);

    //    if (upd)
    //    {
    //    }
    //    return upd;
    return 0;
}
NG_WiFi ng_WiFi;