#include "rom_strings.h"

ROM_Str::ROM_Str(const char *pstr) : str(pstr), len(strlen(pstr)) {}

bool ROM_Str::equals(const char *tstr)
{
    return strncmp_P(tstr, str, len) == 0;
}