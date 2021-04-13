#include "rom_strings.h"

ROM_Str::ROM_Str(const char *pstr) : str(pstr), len(strlen_P(pstr)) {}

bool ROM_Str::equals(const char *tstr) const
{
    return strncmp_P(tstr, str, len) == 0;
}

//NG_model, NG_version, NG_uuid

static const char NG_MODEL[] PROGMEM = "Niagara";
ROM_Str NG_model = ROM_Str(NG_MODEL);

static const char NG_VERSION[] PROGMEM = "0.01";
ROM_Str NG_version = ROM_Str(NG_VERSION);

/*
===== platformio.ini =====
build_flags = !gen_flags.cmd

===== gen_flags.cmd =====
@echo off
for /f %%i in ('uuidgen.exe') do set RESULT=%%i
echo -D UUID=\"%RESULT%\"
*/
#ifndef UUID
#define UUID "UUID-not-set"
#endif
static const char NG_UUID[] PROGMEM = UUID;
ROM_Str NG_uuid = ROM_Str(NG_UUID);


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

static const char MIN_STEP_DELAY_USEC_EXPORT[] PROGMEM = "min_step_delay_usec";
ROM_Str MIN_STEP_DELAY_USEC_export = ROM_Str(MIN_STEP_DELAY_USEC_EXPORT);

static const char MAX_STEP_DELAY_USEC_EXPORT[] PROGMEM = "max_step_delay_usec";
ROM_Str MAX_STEP_DELAY_USEC_export = ROM_Str(MAX_STEP_DELAY_USEC_EXPORT);
