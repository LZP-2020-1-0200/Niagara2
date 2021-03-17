/* File clock.h  */
#ifndef NIAGARA2_CLOCK_H
#define NIAGARA2_CLOCK_H

#define CLK_SECOND (1 << 0) // new epoch second has started
#define CLK_UPTIME (1 << 1) // new uptime second has started

#define CLK_LOCAL_TIME_LEN 25
// buffer length to store ctime() result
// note that ctime buffer is 26 characters long
// "Tue Mar 16 13:43:55 2021\n\0"
// but we trim it before "\n"

#include <Arduino.h>
class NGclock
{
private:
    uint32 uptime_f;      //system uptime in s
    uint32 old_usec;      // for counting uptime
    time_t sync_time_s_f; //epoch time
    uint32 sync_usec_f;   //usec @ last epoch update
    char local_time_f[CLK_LOCAL_TIME_LEN] = {0};

public:
    NGclock(/* args */);
    ~NGclock();
    int sync(const uint32 &new_u, const time_t &new_s);
    const uint32 one_million = 1000000;
    uint32 uptime(void) const { return uptime_f; }
    time_t epoch_s(void) const { return sync_time_s_f; }
    uint32 sync_usec(void) const { return sync_usec_f; }
    const size_t local_time_len = CLK_LOCAL_TIME_LEN;
    char *local_time(void) { return local_time_f; }
};

extern NGclock ngclk;
#endif /* !NIAGARA2_CLOCK_H */