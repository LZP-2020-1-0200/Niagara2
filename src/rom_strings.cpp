#include "rom_strings.h"

ROM_Str::ROM_Str(const char *pstr) : str(pstr), len(strlen_P(pstr)) {}

bool ROM_Str::equals(const char *tstr)
{
    return strncmp_P(tstr, str, len) == 0;
}

static const char INDEX_HTML_PATH[] PROGMEM = "/index.html";
ROM_Str INDEX_HTML_path = ROM_Str(INDEX_HTML_PATH);