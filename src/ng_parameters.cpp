#include "ng_parameters.h"
#include "stepper.h"
#include "buffers.h"

NG_param::NG_param(ROM_Str *_html_path,              //
                   ROM_Str *_field,                  //
                   ROM_Str *_json_file,              //
                   ROM_Str *_config_filename,        //
                   void (*_set_func)(const char *),  //
                   void (*_get_func)(JsonDocument &) //
                   )
    : html_path(_html_path),
      field(_field),
      json_filename(_json_file),
      config_filename(_config_filename),
      set(_set_func),
      get(_get_func)
{
}

NG_param::~NG_param()
{
}

static const char PATH_NONE[] PROGMEM = "none";
ROM_Str PATH_none = ROM_Str(PATH_NONE);
void dummy_get(JsonDocument &local_doc) { local_doc[FPSTR(PATH_none.str)] = 7; }
void dummy_set(const char *args) { return; }

void get_step_delay_usec(JsonDocument &local_doc)
{
    const String field = FPSTR(rs_stepper_direction.str);
    Serial.println(field);
    local_doc[field] = stepper.get_step_delay_usec();
}

void exp_RO_str(JsonDocument &_doc, ROM_Str &_field, ROM_Str &_val)
{
    char *field = tmp.buf();
    const int field_buf_len = tmp.len;
    strncpy_P(field, _field.str, field_buf_len);

    char *val = tmp2.buf();
    const int val_buf_len = tmp2.len;
    strncpy_P(val, _val.str, val_buf_len);

    _doc[field] = val;
}

void get_stepper_direction(JsonDocument &local_doc)
{
    //const char * field = rs_stepper_direction.str;
    switch (stepper.get_direction())
    {
    case STEPPER_DOWN:
        exp_RO_str(local_doc, rs_stepper_direction, rs_stepper_down);
        break;
    case STEPPER_UP:
        exp_RO_str(local_doc, rs_stepper_direction, rs_stepper_up);
        break;
    default:
        exp_RO_str(local_doc, rs_stepper_direction, rs_stepper_pause);
    }
}

NG_param ngp_table[] = {
    NG_param(
        &STEPPER_HTML_path, &STEP_DELAY_USEC_formfield,
        &STEPPER_JSON_path, &PATH_none, [](const char *a) {
            const uint32 delay = atoi(a);
            stepper.set_step_delay_usec(delay); },
        [](JsonDocument &d) {
            //    const String field = STEP_DELAY_USEC_formfield.str;
            //const String field = FPSTR(STEP_DELAY_USEC_formfield.str);
            //const char * field = FPSTR(STEP_DELAY_USEC_formfield.str);
            //Serial.println(field);
            d[FPSTR(STEP_DELAY_USEC_formfield.str)] = stepper.get_step_delay_usec();
        }
        //get_step_delay_usec
        ),

    NG_param(
        &PATH_none, &STEPPER_POSITION_export,
        &STEPPER_JSON_path, &PATH_none, dummy_set,
        [](JsonDocument &d) {
            // const String fi = STEPPER_POSITION_export.str;
            d[FPSTR(STEPPER_POSITION_export.str)] = stepper.get_position();
        }),

    NG_param(
        &PATH_none, &MIN_STEP_DELAY_USEC_export,
        &STEPPER_JSON_path, &PATH_none, dummy_set,
        [](JsonDocument &d) {
            // const String fi = STEPPER_POSITION_export.str;
            d[FPSTR(MIN_STEP_DELAY_USEC_export.str)] = MIN_STEP_DELAY_USEC;
        }),

    NG_param(
        &PATH_none, &MAX_STEP_DELAY_USEC_export,
        &STEPPER_JSON_path, &PATH_none, dummy_set,
        [](JsonDocument &d) {
            d[FPSTR(MAX_STEP_DELAY_USEC_export.str)] = MAX_STEP_DELAY_USEC;
        }),

    NG_param(
        &STEPPER_HTML_path, &rs_stepper_direction,
        &STEPPER_JSON_path, &PATH_none,
        [](const char *a) {
            stepper_direction_t d = STEPPER_PAUSE;
            if (rs_stepper_down.equals(a))
                d = STEPPER_DOWN;
            else if (rs_stepper_up.equals(a))
                d = STEPPER_UP;
            stepper.set_direction(d);
        },
        get_stepper_direction),

    NG_param(nullptr, nullptr, nullptr, nullptr, dummy_set, dummy_get) // last one is nullptr
};

bool params_export(const char *j_path, RW_buffer &target)
{
    bool path_found = false;
    const int capacity = JSON_OBJECT_SIZE(10);
    StaticJsonDocument<capacity> doc;

    for (NG_param *ngp = ngp_table; ngp->json_filename; ngp++)
    {
        if (ngp->json_filename->equals(j_path))
        {
            path_found = true;
            ngp->get(doc);
        }
    }

    if (path_found)
    {
        serializeJson(doc, json_buf.buf(), json_buf.len);
    }
    return path_found;
}
