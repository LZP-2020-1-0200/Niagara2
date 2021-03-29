#include "NG_WebServer.h"
ESP8266WebServer server(80);

const char *text_plain = "text/plain";

void NG_WebServer_init(void)
{
    static bool NG_WebServer_initialized = false;
    if (NG_WebServer_initialized)
        return;
    NG_WebServer_initialized = true;

    server.on("/", []() {
        server.send(200, text_plain, "This is an index page.");
        Serial.println(F("serving index"));
    });
    server.onNotFound([]() { // If the client requests any URI
                             //  server.send(200, "text/plain", "this works as well");
        //     if (!handleFileRead(server.uri()))                    // send it if it exists
        server.send(404, text_plain , "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
        Serial.println(F("404: Not Found"));

    });
    server.begin();
}