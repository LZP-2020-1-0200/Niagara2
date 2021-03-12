/* File blink.h */
#ifndef NIAGARA2_BLINK_H
#define NIAGARA2_BLINK_H
#include <Arduino.h>
class Blink
{
private:
    /* data */
public:
    Blink(/* args */);
    ~Blink();
    int exec(const uint32 &new_u, const time_t &new_s);
};





extern Blink blink;

#endif /* !NIAGARA2_BLINK_H */