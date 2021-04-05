#include "NG_WebServer.h"
#include "LittleFS.h"
#include "rom_strings.h"
#include "ng_parameters.h"
#include "buffers.h"

ESP8266WebServer server(80);

const char *text_plain = "text/plain";

//path_index_html

void handle_form_data(const int &args_count, const String &path_s)
{
    const char *path = path_s.c_str();
    Serial.print("args_count = ");
    Serial.println(args_count);

    for (int arg_n = 0; arg_n < args_count; arg_n++)
    {
        const char *argName = server.argName(arg_n).c_str();
        Serial.print(F("argName = "));
        Serial.println(argName);

        const char *val = server.arg(arg_n).c_str();
        Serial.print(F("arg = "));
        Serial.println(val);

        for (NG_param *ngp = ngp_table; ngp->html_path; ngp++)
        {
            if (ngp->html_path->equals(path) && ngp->field->equals(argName))
            {
                Serial.println("###############atrasts");
                ngp->set(val);
            }
        }
    }
}

bool handleFileRead(String path)
{ // send the right file to the client (if it exists)
    Serial.print(F("handleFileRead: "));
    Serial.println(path);
    if (path.endsWith("/"))
        path += "index.html"; // If a folder is requested, send the index file

    String contentType = mime::getContentType(path);
    Serial.println(contentType);

    if (path.endsWith(F(".json")))
    { //deliver json
        const char *js_path = path.c_str();

        
        //StaticJsonDocument<export_capacity> doc;
        //DynamicJsonDocument doc(1000);

        bool json_found = params_export(js_path, json_buf);
  
        if (json_found)
        {
            //serializeJson(doc, json_buf.buf(), json_buf.len);
            server.send(200, contentType, json_buf.buf());
        }

        return json_found;
    }
    else
    { //deliver file
        const int server_args_n = server.args();
        if (server_args_n)
        {
            handle_form_data(server_args_n, path);
        }

        if (LittleFS.exists(path))
        {                                                       // If the file exists
            File file = LittleFS.open(path, "r");               // Open it
            size_t sent = server.streamFile(file, contentType); // And send it to the client
            Serial.print(F("Sent "));
            Serial.println(sent);
            file.close(); // Then close the file again
            return true;
        }
        Serial.println(F("\tFile Not Found"));
        return false; // If the file doesn't exist, return false
    }
}

void NG_WebServer_init(void)
{
    static bool NG_WebServer_initialized = false;
    if (NG_WebServer_initialized)
        return;
    NG_WebServer_initialized = true;

    //    server.on("/", []() {
    //        server.send(200, text_plain, "This is an index page.");
    //        Serial.println(F("serving index"));
    //    });
    server.onNotFound([]() {                                // If the client requests any URI
                                                            //  server.send(200, "text/plain", "this works as well");
        if (!handleFileRead(server.uri()))                  // send it if it exists
            server.send(404, text_plain, "404: Not Found"); // otherwise, respond with a 404 (Not Found) error

    });
    server.begin();
}