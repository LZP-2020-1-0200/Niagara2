#include "ngWiFi.h"
#include "NGclock.h"
#include "rom_strings.h"

NG_WiFi::NG_WiFi(/* args */) : refresh_period_usec(ngclk.one_million)
{
    station_status = -1; // indicate that wifi_station_get_connect_status() was not executed
    // station_status_t is an enum in range 0..5
    n_scanNetworksFound = 0;
    prev_usec = 0;

    //load existing station config
    struct station_config sta_conf;
    wifi_station_get_config(&sta_conf);

    if (sizeof(sta_conf.ssid) == SSID_MAX_LEN)
    {
        memcpy(sta_ssid, sta_conf.ssid, SSID_MAX_LEN);
        sta_ssid[SSID_MAX_LEN] = 0;
    }
    if (sizeof(sta_conf.password) == PSK_PASS_MAX_LEN)
    {
        memcpy(sta_psk, sta_conf.password, PSK_PASS_MAX_LEN);
        sta_psk[PSK_PASS_MAX_LEN] = 0;
    }
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

int8_t NG_WiFi::scan(void)
{
    n_scanNetworksFound = WiFi.scanNetworks();
    return n_scanNetworksFound;
}

ssid_result NG_WiFi::set_STA_SSID(const char *new_ssid)
{
    const size_t new_ssid_len = strlen(new_ssid);
    if (new_ssid_len > SSID_MAX_LEN)
    {
        return SSID_TOO_LONG;
    }
    if (new_ssid_len < 1)
    {
        return SSID_TOO_SHORT;
    }
    memcpy(sta_ssid, new_ssid, new_ssid_len);
    sta_ssid[new_ssid_len] = 0;
    return SSID_OK;
}

void NG_WiFi::print_sta_ssid(void)
{
    Serial.printf_P(PSTR("sta-ssid = %s" EOL), sta_ssid);
}

psk_pass_result NG_WiFi::set_STA_PSK(const char *new_pass)
{
    const size_t new_pass_len = strlen(new_pass);
    if (new_pass_len > PSK_PASS_MAX_LEN)
    {
        return PSK_PASS_TOO_LONG;
    }
    if (new_pass_len < PSK_PASS_MIN_LEN)
    {
        return PSK_PASS_TOO_SHORT;
    }
    memcpy(sta_psk, new_pass, new_pass_len);
    sta_psk[new_pass_len] = 0;
    return PSK_PASS_OK;
}
void NG_WiFi::STA_connect(void)
{
    WiFi.disconnect();
    WiFi.begin(sta_ssid, sta_psk);
}

NG_WiFi ng_WiFi;