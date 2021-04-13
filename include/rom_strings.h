/* File rom_strings.h */
#ifndef NIAGARA2_ROM_STRINGS_H
#define NIAGARA2_ROM_STRINGS_H

#include <Arduino.h>

#define EOL "\r\n"

class ROM_Str
{
private:
    /* data */

public:
    const char *str;
    const size_t len;
    bool equals(const char *) const;
    ROM_Str(const char *);
    ~ROM_Str(){};
};

extern ROM_Str NG_model;
extern ROM_Str NG_version;
extern ROM_Str NG_uuid;

extern ROM_Str STEPPER_HTML_path;
extern ROM_Str STEP_DELAY_USEC_formfield;
extern ROM_Str STEPPER_JSON_path;
extern ROM_Str STEPPER_POSITION_export;
extern ROM_Str MIN_STEP_DELAY_USEC_export;
extern ROM_Str MAX_STEP_DELAY_USEC_export;
extern ROM_Str CONFIG_JSON_path;

#endif /* !NIAGARA2_ROM_STRINGS_H */
