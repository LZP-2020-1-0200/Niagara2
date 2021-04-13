/* File ng_parameters.h */
#ifndef NIAGARA2_NG_PARAMETERS_H
#define NIAGARA2_NG_PARAMETERS_H
#include "rom_strings.h"
#include <ArduinoJson.h>
#include "buffers.h"
bool params_export(const char *j_path, RW_buffer &target);

class NG_param
{
private:
    /* data */
public:
    NG_param(ROM_Str *_html_path,              //
             ROM_Str *_field,                  //
             ROM_Str *_json_file,              //
             ROM_Str *_config_filename,        //
             void (*_set_func)(const char *),  //
             void (*_get_func)(JsonDocument &) //
    );
    ~NG_param();
    const ROM_Str *html_path;
    const ROM_Str *field;
    const ROM_Str *json_filename;
    const ROM_Str *config_filename;
    void (*set)(const char *);
    void (*get)(JsonDocument &);
};

extern NG_param ngp_table[];

#endif /* NIAGARA2_NG_PARAMETERS_H */