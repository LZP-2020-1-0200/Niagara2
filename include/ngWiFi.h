/* File ngWiFi.h */
#ifndef NIAGARA2_WIFI_H
#define NIAGARA2_WIFI_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <user_interface.h>

#define SSID_MAX_LEN 32
enum ssid_result
{
    SSID_TOO_LONG = -2,
    SSID_TOO_SHORT = -1,
    SSID_OK = 0
};

#define PSK_PASS_MAX_LEN 64
#define PSK_PASS_MIN_LEN 8
enum psk_pass_result
{
    PSK_PASS_TOO_LONG = -2,
    PSK_PASS_TOO_SHORT = -1,
    PSK_PASS_OK = 0
};

class NG_WiFi
{
private:
    /* data */
    int station_status; // station_status_t is enum
    uint32 prev_usec;
    const uint32 refresh_period_usec;
    int8_t n_scanNetworksFound;
    char sta_ssid[SSID_MAX_LEN + 1] = {0};
    char sta_psk[PSK_PASS_MAX_LEN + 1] = {0};

public:
    NG_WiFi(/* args */);
    ~NG_WiFi();
    int exec(const uint32 &new_u);
    bool got_ip(void) const { return station_status == STATION_GOT_IP; }
    int8_t scan(void);
    ssid_result set_STA_SSID(const char *);
    const char *get_STA_SSID() const { return sta_ssid; };
    psk_pass_result set_STA_PSK(const char *);
    const char *get_STA_PSK() const { return sta_psk; };
    void STA_connect(void);
};
extern NG_WiFi ng_WiFi;
#endif /* NIAGARA2_WIFI_H */