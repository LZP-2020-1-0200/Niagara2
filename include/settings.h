/* File settings.h  */
#ifndef NIAGARA2_SETTINGS_H
#define NIAGARA2_SETTINGS_H

//#include <Arduino.h>
#define DEFAULT_BAUD 74880

class Settings
{
private:
    /* data */
public:
    Settings(/* args */);
    ~Settings();
    void load(void);

};

extern Settings settings;

#endif /* !NIAGARA2_SETTINGS_H */