#include "ngWiFi.h"
#include "NGclock.h"
#include <ESP8266WiFi.h>
#include "NG_WebServer.h"

NG_WiFi::NG_WiFi(/* args */) : refresh_period_usec(ngclk.one_million)
{
    station_status = -1; // indicate that wifi_station_get_connect_status() was not executed
    // station_status_t is an enum in range 0..5

    prev_usec = 0;
}

NG_WiFi::~NG_WiFi()
{
}

int NG_WiFi::exec(const uint32 &new_u)
{
    const uint32 dt = new_u - prev_usec;
    if (dt >= refresh_period_usec)
    {
        prev_usec += refresh_period_usec;
        station_status_t new_station_status = wifi_station_get_connect_status();
        if (station_status != new_station_status)
        {
            station_status = new_station_status;

            Serial.print(F("station_status = "));

            switch (station_status)
            {
            case STATION_IDLE:
                Serial.println(F("idle"));
                break;
            case STATION_CONNECTING:
                Serial.println(F("connecting"));
                break;
            case STATION_WRONG_PASSWORD:
                Serial.println(F("wrong_password"));
                break;
            case STATION_NO_AP_FOUND:
                Serial.println(F("no_ap_found"));
                break;
            case STATION_CONNECT_FAIL:
                Serial.println(F("connect_fail"));
                break;
            case STATION_GOT_IP:
                Serial.println(F("got_ip"));
                Serial.print(F("ip_addr = "));
                Serial.println(WiFi.localIP());
            }
            return 1;
        }
    }
    return 0;
}
NG_WiFi ng_WiFi;