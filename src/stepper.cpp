#include "stepper.h"
#include "rom_strings.h"
Stepper stepper;
Stepper::Stepper(/* args */)
{
    position = 0;
    direction = STEPPER_DOWN;
    prev_usec = 0;
    step_delay_usec = 5000;
    pinMode(STEPPER_LINE1, OUTPUT);
    pinMode(STEPPER_LINE2, OUTPUT);
    pinMode(STEPPER_LINE3, OUTPUT);
    pinMode(STEPPER_LINE4, OUTPUT);
}

int Stepper::exec(const uint32 &new_usec)
{
    const uint32 dt = new_usec - prev_usec;
    if (dt < step_delay_usec)
    {
        return 0;
    }
    prev_usec += step_delay_usec;

    position += direction;

    // table from SAA1027 Stepper Motor Driver IC
    static const uint8_t Q1[] = {LOW, HIGH, HIGH, LOW};
    static const uint8_t Q2[] = {HIGH, LOW, LOW, HIGH};
    static const uint8_t Q3[] = {LOW, LOW, HIGH, HIGH};
    static const uint8_t Q4[] = {HIGH, HIGH, LOW, LOW};
    const int phase = position & 0x3;

    if (direction)
    {
        digitalWrite(STEPPER_LINE1, Q1[phase]);
        digitalWrite(STEPPER_LINE2, Q2[phase]);
        digitalWrite(STEPPER_LINE3, Q3[phase]);
        digitalWrite(STEPPER_LINE4, Q4[phase]);
    }
    else
    { // turn off all lines
        static const uint8_t stepper_off = LOW;
        digitalWrite(STEPPER_LINE1, stepper_off);
        digitalWrite(STEPPER_LINE2, stepper_off);
        digitalWrite(STEPPER_LINE3, stepper_off);
        digitalWrite(STEPPER_LINE4, stepper_off);
    }

    return direction;
}

void Stepper::set_step_delay_usec(const uint32 &usec)
{
    step_delay_usec = usec;
    if (step_delay_usec < MIN_STEP_DELAY_USEC)
    {
        step_delay_usec = MIN_STEP_DELAY_USEC;
        Serial.println(F("MIN_STEP_DELAY_USEC"));
    }
    if (step_delay_usec > MAX_STEP_DELAY_USEC)
    {
        step_delay_usec = MAX_STEP_DELAY_USEC;
        Serial.println(F("MAX_STEP_DELAY_USEC"));
    }
    Serial.print(F("step_delay_usec = "));
    Serial.println(step_delay_usec);
}

//void Stepper::set_direction(const char *dstr)
//{
//    stepper_direction_t d = STEPPER_PAUSE;
//    if (rs_stepper_down.equals(dstr))
//        d = STEPPER_DOWN;
//    else if (rs_stepper_up.equals(dstr))
//        d = STEPPER_UP;
//    set_direction(d);
//}