/* File task.h */
#ifndef NIAGARA2_TASK_H
#define NIAGARA2_TASK_H

#include <Arduino.h>
class NG_Task
{
private:
    const uint32 start_delay_usec;
public:
    NG_Task(const uint32 & start_usec, const uint32 period_usec);
    ~NG_Task();
    int exec(const uint32 &);
    uint32 delta_usec(void) const { return delta_usec_f; }

protected:
    uint32 usec_f;
    uint32 last_exec_f;

    uint32 usec_period_f;
    uint32 delta_usec_f;

};

#endif /* NIAGARA2_TASK_H */