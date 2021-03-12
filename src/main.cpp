#include <Arduino.h>

#include <user_interface.h>
#include "NGclock.h"

//#include "LittleFS.h"
#include "settings.h"
void setup()
{
  settings.load();
}

void loop()
{
  const time_t new_secs = time(nullptr);
  const uint32 new_usec = system_get_time();

  const int clk_rez = ngclk.sync(new_usec, new_secs);
  if (clk_rez & CLK_UPTIME)
  {
    Serial.print(F("sync_usec = "));
    Serial.println(ngclk.sync_usec());

    Serial.print(F("uptime = "));
    Serial.println(ngclk.uptime());

    Serial.print(F("Epoch = "));
    Serial.println(ngclk.epoch_s());

    Serial.println(ngclk.local_time());

    return;
  }




  //  if (ngclk.exec(new_usec))
  //  {
  //   Serial.print(F("time(nullptr)=\t"));
  //   Serial.println(new_secs);
  //   Serial.print(F("system_get_time()=\t"));
  //   Serial.println(new_usec);
  //   Serial.print(F("ngclk.delta_usec()=\t"));
  //   Serial.println(ngclk.delta_usec());
  //   Serial.print(F("ngclk.uptime()=\t"));
  //   Serial.println(ngclk.uptime());
  //    return;
  // }

  //  task
  // put your main code here, to run repeatedly://
  //if task.execute() return
}
