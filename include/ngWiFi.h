/* File ngWiFi.h */
#ifndef NIAGARA2_WIFI_H
#define NIAGARA2_WIFI_H
#include <Arduino.h>
#include <user_interface.h>

class NG_WiFi
{
private:
    /* data */
    int station_status; // station_status_t is enum
    uint32 prev_usec;
    const uint32 refresh_period_usec;

public:
    NG_WiFi(/* args */);
    ~NG_WiFi();
    int exec(const uint32 &new_u);
    bool got_ip(void) const { return station_status == STATION_GOT_IP; }
};
extern NG_WiFi ng_WiFi;
#endif /* NIAGARA2_WIFI_H */