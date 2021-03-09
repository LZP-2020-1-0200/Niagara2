#include "ngWiFi.h"
#include "init.h"
#include <ESP8266WiFi.h>

NG_WiFi::NG_WiFi(/* args */) : NG_Task(0, 1000000)
{
   // initialization_report(F("initializing NG_Task"));
   //  WiFi.begin("Optika", "slepens123");

}

NG_WiFi::~NG_WiFi()
{
}

int NG_WiFi::exec(const uint32 &new_u)
{
    int upd = NG_Task::exec(new_u);

    if (upd)
    {
    }
    return upd;
}
NG_WiFi ng_WiFi;