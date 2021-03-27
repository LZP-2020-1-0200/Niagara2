#include "task.h"
#include "Niagara2_generated.h"
#include "ngWiFi.h"
#include "ESP8266WiFiType.h"

Command::Command(const char *cmd_str, void (*ptr_func)(const char *)) //
    : cmd(cmd_str),
      cmd_len(strlen_P(cmd_str)),
      func(ptr_func)
{ // Regular constructor for command-function pairs
}

Command::Command(void (*ptr_func)(const char *)) //
    : cmd(nullptr),
      cmd_len(0),
      func(ptr_func)
{ // Special constructor for handling unknown commands
} // This error function must be the last one last in the cmd_list!

void HELP_func(const char *); // implementation requires cmd_list, see below
static int echo_on = 1;

Command cmd_list[] = {
    //command-function pairs
    Command("*IDN?", [](const char *a) {
        Serial.printf("%s %s %s" EOL, NG_model, NG_version, NG_uuid);
    }),

    Command("ECHO", [](const char *a) {
        if (*a == '1')
            echo_on = 1;
        else
            echo_on = 0;
        Serial.printf("echo = %d" EOL, echo_on);
    }),

    Command("*RST", [](const char *a) {
        Serial.println("waiting for WDT ...");
        while (true)
            ;
    }),

    Command("SCAN", [](const char *a) {
        int8_t n_NetworksFound = ng_WiFi.scan();
        if (n_NetworksFound == WIFI_SCAN_RUNNING)
        {
            Serial.println("WIFI_SCAN_RUNNING");
            return;
        }
        if (n_NetworksFound == WIFI_SCAN_FAILED)
        {
            Serial.println("WIFI_SCAN_FAILED");
            return;
        }
        if (n_NetworksFound)
        {
            for (int i = 0; i < n_NetworksFound; i++)
                Serial.printf("%s %d" EOL, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
        }
        else
            Serial.println("no access points found");
        WiFi.scanDelete();
    }),

    Command("STA-SSID", [](const char *a) {
        switch (ng_WiFi.set_STA_SSID(a))
        {
        case SSID_TOO_LONG:
            Serial.println("SSID_TOO_LONG");
            break;
        case SSID_TOO_SHORT:
            Serial.println("SSID_TOO_SHORT");
            break;
        case SSID_OK:
            Serial.printf("sta-ssid = %s" EOL, ng_WiFi.get_STA_SSID());
        }
    }),

    Command("STA-PSK", [](const char *a) {
        switch (ng_WiFi.set_STA_PSK(a))
        {
        case PSK_PASS_TOO_LONG:
            Serial.println("PSK_PASS_TOO_LONG");
            break;
        case PSK_PASS_TOO_SHORT:
            Serial.println("PSK_PASS_TOO_SHORT");
            break;
        case PSK_PASS_OK:
            Serial.printf("sta_psk = %s" EOL, ng_WiFi.get_STA_PSK());
        }
    }),

    Command("CONNECT", [](const char *a) {
        ng_WiFi.STA_connect();
    }),


    Command("HELP", HELP_func), //
    Command([](const char *a) { // error function must be last!
        Serial.printf("ERROR: UNKNOWN COMMAND %s" EOL, a);
    })};

void HELP_func(const char *args)
{
    Serial.println(F("Available commands:"));
    for (Command *cl = cmd_list; cl->cmd; cl++)
    {
        Serial.println(cl->cmd);
    }
}

void parse(char *cmd_line, int cmd_line_len)
{
    if (cmd_line_len)
    {
        Command *cl = cmd_list;
        int cmd_num = 0;
        for (; cl->cmd; cl++)
        { // search for known commands
            if (0 == strncasecmp_P(cmd_line, cl->cmd, cl->cmd_len))
            { // known command found
                char *argument = &cmd_line[cl->cmd_len];
                while (*argument == ' ' || *argument == '\t')
                { // step over empty spaces between command and arguments
                    argument++;
                }
                cl->func(argument); //call the known function
                return;
            }
            cmd_num++;
        }
        cl->func(cmd_line); // this will call cmd_list -> ERROR_func
    }
    else
        Serial.println(F("Empty line"));
}

void task_addChar(char ch)
{
    static char cmd_line[MAX_CMD_LEN + 1]; // buffer
    static int n = 0;                      // current char position
    if (echo_on)
        Serial.print(ch); // echo
    if (ch == 10)
        return; // ignore  (LF)

    if (ch == 13)
    {           // end of line
        ch = 0; // replace char by zero terminator
    }
    cmd_line[n++] = ch; // insert symbol

    if (ch == 0)
    {
        if (echo_on)
            Serial.println();
        parse(cmd_line, n - 1);
        n = 0;
    }
    if (n >= MAX_CMD_LEN)
    { // buffer overflow
        n = 0;
    }
}
