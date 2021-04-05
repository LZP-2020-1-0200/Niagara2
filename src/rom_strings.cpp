#include "rom_strings.h"

ROM_Str::ROM_Str(const char *pstr) : str(pstr), len(strlen_P(pstr)) {}

bool ROM_Str::equals(const char *tstr) const
{
    return strncmp_P(tstr, str, len) == 0;
}

static const char STEPPER_HTML_PATH[] PROGMEM = "/stepper.html";
ROM_Str STEPPER_HTML_path = ROM_Str(STEPPER_HTML_PATH);

static const char STEP_DELAY_USEC_FORMFIELD[] PROGMEM = "step_delay_usec";
ROM_Str STEP_DELAY_USEC_formfield = ROM_Str(STEP_DELAY_USEC_FORMFIELD);

static const char STEPPER_JSON_PATH[] PROGMEM = "/stepper.json";
ROM_Str STEPPER_JSON_path = ROM_Str(STEPPER_JSON_PATH);

static const char CONFIG_JSON_PATH[] PROGMEM = "/config.json";
ROM_Str CONFIG_JSON_path = ROM_Str(CONFIG_JSON_PATH);

static const char STEPPER_POSITION_EXPORT[] PROGMEM = "stepper_position";
ROM_Str STEPPER_POSITION_export = ROM_Str(STEPPER_POSITION_EXPORT);

