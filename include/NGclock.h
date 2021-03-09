/* File clock.h  */
#ifndef NIAGARA2_CLOCK_H
#define NIAGARA2_CLOCK_H

#include "task.h"

class NGclock : public NG_Task
{
private:
    /* data */
    uint32 uptime_f;
    time_t sync_time_s_f;
    uint32 sync_usec_f;

public:
    NGclock(/* args */);
    ~NGclock();
    int delta_t();
    int exec(const uint32 &new_u);
    int sync(const uint32 &new_u, const time_t &new_s);
    uint32 uptime(void) const { return uptime_f; }

    time_t sync_time_s(void) const { return sync_time_s_f; }
    uint32 sync_usec(void) const { return sync_usec_f; }
};

extern NGclock ngclk;
#endif /* !NIAGARA2_CLOCK_H */