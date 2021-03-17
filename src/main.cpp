#include <Arduino.h>

#include <user_interface.h>
#include "NGclock.h"

//#include "LittleFS.h"
#include "blink.h"
#include "settings.h"

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include "ngWiFi.h"
#include "NG_WebServer.h"

void setup()
{
  settings.load();
  NG_WebServer_init();
}

void loop()
{
  const time_t new_secs = time(nullptr);
  const uint32 new_usec = system_get_time();

  if (ngclk.sync(new_usec, new_secs))
  {
    return;
  }
  if (blink.exec(new_usec, new_secs))
  {
    //Serial.println(new_usec);
    return;
  }

  if (ng_WiFi.exec(new_usec))
    return;
  if (ng_WiFi.got_ip())
    server.handleClient();
  // put your main code here, to run repeatedly://
  //Serial.print(".");
}
