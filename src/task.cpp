#include "task.h"
#include "init.h"

NG_Task::NG_Task(const uint32 &start_usec, const uint32 period_usec) : start_delay_usec(start_usec)
{

    delta_usec_f = 0;
    usec_f = start_usec;
    last_exec_f = start_usec;
    usec_period_f = period_usec;
}

NG_Task::~NG_Task()
{
}

int NG_Task::exec(const uint32 &new_u)
{
    if (start_delay_usec > new_u)
        return 0;

    uint32 dt = new_u - usec_f;

    if (dt >= usec_period_f)
    {
        usec_f += usec_period_f;
        delta_usec_f = new_u - last_exec_f;
        last_exec_f = new_u;
        return 1;
    }
    return 0;
}
