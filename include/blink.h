/* File blink.h */
#ifndef NIAGARA2_BLINK_H
#define NIAGARA2_BLINK_H
#include <Arduino.h>

#define LED_TURNED_ON (1 << 0)
#define LED_TURNED_OFF (1 << 1)

class Blink
{
private:
    uint32 start_usec;
    uint32 duration_usec;
    unsigned long on_s;
    uint8_t ledstate;

public:
    Blink(/* args */);
    ~Blink();
    int exec(const uint32 &new_u, const unsigned long &new_s);
};

extern Blink blink;

#endif /* !NIAGARA2_BLINK_H */