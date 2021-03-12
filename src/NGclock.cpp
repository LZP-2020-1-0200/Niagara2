#include "NGclock.h"
#include <time.h>
#include <string.h>

NGclock::NGclock()
{
    uptime_f = 0;      //system uptime in s
    old_usec = 0;      // for counting uptime
    sync_time_s_f = 0; //epoch time
    sync_usec_f = 0;   //usec@epoch update
    setTZ("EET-2EEST,M3.5.0/3,M10.5.0/4");
}

NGclock::~NGclock()
{
}

int NGclock::sync(const uint32 &new_u, const time_t &new_s)
{
    int ret_val = 0;
    if (sync_time_s_f != new_s)
    {
        sync_time_s_f = new_s;
        sync_usec_f = new_u;
        ret_val ^= CLK_SECOND;
        strlcpy(local_time_f, ctime(&sync_time_s_f), local_time_len);
    }

    uint32 dt = new_u - old_usec;
    if (dt >= one_million)
    {
        old_usec += one_million;
        uptime_f++;
        ret_val ^= CLK_UPTIME;
    }

    return ret_val;
}
NGclock ngclk;