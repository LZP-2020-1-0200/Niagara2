#include "NGclock.h"
#include "init.h"

NGclock::NGclock(/* args */) : NG_Task(0, 1000000)
{
    initialization_report(F("initializing NGclock"));
    uptime_f = 0;
    sync_time_s_f = 0;
    sync_usec_f = 0;
    setTZ("EET-2EEST,M3.5.0/3,M10.5.0/4");
}

int NGclock::delta_t()
{

    return 0;
}
NGclock::~NGclock()
{
}
int NGclock::exec(const uint32 &new_u)
{
    int upd = NG_Task::exec(new_u);
    if (upd)
        uptime_f++;

    return upd;
}

int NGclock::sync(const uint32 &new_u, const time_t &new_s)
{
    if (sync_time_s_f == new_s)
        return 0;
    sync_time_s_f = new_s;
    sync_usec_f = new_u;
    return 1;
}

NGclock ngclk;