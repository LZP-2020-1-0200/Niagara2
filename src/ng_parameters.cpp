#include "ng_parameters.h"
#include "stepper.h"

NG_param::NG_param(ROM_Str *html_path,              //
                   ROM_Str *html_formfield,         //
                   ROM_Str *json_file,              //
                   void (*set_func)(const char *),  //
                   void (*get_func)(JsonDocument &) //
                   )
    : path(html_path),
      formfield(html_formfield),
      json_filename(json_file),
      set(set_func),
      get(get_func)
{
}

NG_param::~NG_param()
{
}

void dummy_set(const char *args) { return; }
void dummy_get(JsonDocument &local_doc)
{
    local_doc["dummy"] = 7;
}

void get_step_delay_usec(JsonDocument &local_doc)
{
    //local_doc["dummy"] = 7;
    const String field = FPSTR(STEP_DELAY_USEC_formfield.str);
    Serial.println(field);
    local_doc[field] = stepper.get_step_delay_usec();
}

NG_param ngp_table[] = {
    NG_param(
        &STEPPER_HTML_path, &STEP_DELAY_USEC_formfield,
        &STEPPER_JSON_path, [](const char *a) {
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
        &STEPPER_HTML_path, &STEPPER_POSITION_export,
        &STEPPER_JSON_path, dummy_set,
        [](JsonDocument &d) {
           // const String fi = STEPPER_POSITION_export.str;
            d[FPSTR(STEPPER_POSITION_export.str)] = stepper.get_position();
        }),


    NG_param(nullptr, nullptr, nullptr, dummy_set, dummy_get) // last one is nullptr
};

bool params_export(const char *j_path, RW_buffer &target)
{
    bool path_found = false;
    const int capacity = JSON_OBJECT_SIZE(10);
    StaticJsonDocument<capacity> doc;
    //DynamicJsonDocument doc(1000);

    for (NG_param *ngp = ngp_table; ngp->json_filename; ngp++)
    {
        if (ngp->json_filename->equals(j_path))
        {
            path_found = true;
            doc["sss"] = 4;
            ngp->get(doc);
        }
    }

    if (path_found)
    {
        serializeJson(doc, json_buf.buf(), json_buf.len);
    }
    return path_found;
}
//bool param_json_export(char *buffer, const size_t &bufferSize, const char *json_file)
//{

//}