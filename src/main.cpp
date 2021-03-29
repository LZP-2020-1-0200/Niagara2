#include <Arduino.h>

#include <user_interface.h>
#include "NGclock.h"

//#include "LittleFS.h"
#include "blink.h"
#include "settings.h"

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "ngWiFi.h"
#include "NG_WebServer.h"
#include "task.h"

void setup()
{
  settings.load();
  ng_WiFi.print_sta_ssid();
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

  if (Serial.available())
  {
    task_addChar(Serial.read());
    return;
  }

  if (ng_WiFi.got_ip())
    server.handleClient();
  // put your main code here, to run repeatedly://
  //Serial.print(".");
}
