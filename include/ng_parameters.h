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
    NG_param(ROM_Str *html_path,              //
             ROM_Str *field,                  //
             ROM_Str *json_file,              //
             void (*set_func)(const char *),  //
             void (*get_func)(JsonDocument &) //
    );
    ~NG_param();
    const ROM_Str *path;
    const ROM_Str *formfield;
    const ROM_Str *json_filename;
    void (*set)(const char *);
    void (*get)(JsonDocument &);
};

extern NG_param ngp_table[];
//bool param_json_export(char *buffer, const size_t &bufferSize, const char *json_file);

#endif /* NIAGARA2_NG_PARAMETERS_H */