#include <Arduino.h>

#include "init.h"
#include <user_interface.h>
#include "NGclock.h"

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  const time_t new_secs = time(nullptr);
  const uint32 new_usec = system_get_time();

  if (ngclk.sync(new_usec, new_secs))
  {
    Serial.print(F("ngclk.sync_time_s()=\t"));
    Serial.println(ngclk.sync_time_s());
    const time_t t = ngclk.sync_time_s();
    Serial.println(ctime(&t));

    Serial.print(F("ngclk.sync_usec()=\t"));
    Serial.println(ngclk.sync_usec());
    return;
  }

  if (ngclk.exec(new_usec))
  {
    //   Serial.print(F("time(nullptr)=\t"));
    //   Serial.println(new_secs);
    //   Serial.print(F("system_get_time()=\t"));
    //   Serial.println(new_usec);
    //   Serial.print(F("ngclk.delta_usec()=\t"));
    //   Serial.println(ngclk.delta_usec());
    //   Serial.print(F("ngclk.uptime()=\t"));
    //   Serial.println(ngclk.uptime());
    return;
  }

  //  task
  // put your main code here, to run repeatedly://
  //if task.execute() return
}
