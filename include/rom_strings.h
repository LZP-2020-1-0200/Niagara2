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
    bool equals(const char *);
    ROM_Str(const char *);
    ~ROM_Str(){};
};

extern ROM_Str INDEX_HTML_path;

#endif /* !NIAGARA2_ROM_STRINGS_H */
