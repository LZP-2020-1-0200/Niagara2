#include "blink.h"

#include "ngWiFi.h"
Blink blink;

Blink::Blink(/* args */)
{
    start_usec = 0;
    duration_usec = 50000;
    on_s = 0;
    pinMode(LED_BUILTIN, OUTPUT);
    ledstate = HIGH;
    digitalWrite(LED_BUILTIN, ledstate);
}

Blink::~Blink()
{
}

int Blink::exec(const uint32 &new_u, const unsigned long &new_s)
{
    if (new_s < 1615808122)
    {             //Mon Mar 15 13:35:22 2021
        return 0; // no NTP = no blink
    }

    if (on_s != new_s)
    {
        on_s = new_s;
        start_usec = new_u;
        ledstate = LOW;
        digitalWrite(LED_BUILTIN, ledstate);
        return LED_TURNED_ON;
    }
    const uint32 dt = new_u - start_usec;
    if ((dt >= duration_usec) && (ledstate == LOW))
    {
        ledstate = HIGH;
        if (ng_WiFi.got_ip())
        { //  led permanently on if connection lost
            digitalWrite(LED_BUILTIN, ledstate);
        }
        return LED_TURNED_OFF;
    }
    return 0;
}
