/* File stepper.h */
#ifndef NIAGARA2_STEPPER_H
#define NIAGARA2_STEPPER_H
#include <Arduino.h>

enum stepper_direction_t
{
    STEPPER_DOWN = -1,
    STEPPER_PAUSE = 0,
    STEPPER_UP = 1
};

#define STEPPER_LINE1 15
#define STEPPER_LINE2 13
#define STEPPER_LINE3 12
#define STEPPER_LINE4 14


class Stepper
{
private:
    /* data */
    int position;
    stepper_direction_t direction;
    uint32 prev_usec;
    uint32 step_delay_usec;

public:
    Stepper(/* args */);
    ~Stepper(){};
    int exec(const uint32 &);
    int get_position(void) const { return position; }
};

extern Stepper stepper;

#endif /* !NIAGARA2_STEPPER_H */