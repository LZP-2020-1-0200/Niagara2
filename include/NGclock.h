/* File clock.h  */
#ifndef NIAGARA2_CLOCK_H
#define NIAGARA2_CLOCK_H

class NGclock
{
private:
    /* data */
    
public:
    NGclock(/* args */);
    ~NGclock();
    int delta_t();
};


extern NGclock ngclk;
#endif /* !NIAGARA2_CLOCK_H */