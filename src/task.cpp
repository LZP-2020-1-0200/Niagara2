#include "task.h"
#include "ngWiFi.h"
#include "ESP8266WiFiType.h"
#include "rom_strings.h"

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

// keep all strings in PROGMEM
static const char IDN_cmd[] PROGMEM = "*IDN?";
static const char ECHO_cmd[] PROGMEM = "ECHO";
static const char RST_cmd[] PROGMEM = "*RST";
static const char SCAN_cmd[] PROGMEM = "SCAN";
static const char STA_SSID_cmd[] PROGMEM = "STA-SSID";
static const char STA_PSK_cmd[] PROGMEM = "STA-PSK";
static const char CONNECT_cmd[] PROGMEM = "CONNECT";
static const char HELP_cmd[] PROGMEM = "HELP";

static const char IDN_format[] PROGMEM = "%s %s %s" EOL;
static const char ECHO_format[] PROGMEM = "echo = %d" EOL;
static const char romstr_waiting_for_WDT[] PROGMEM = "Waiting for watchdog timer ..." EOL;
static const char wifi_scan_running[] PROGMEM = "wifi scan running" EOL;
static const char wifi_scan_failed[] PROGMEM = "wifi scan failed" EOL;
static const char scan_result_format[] PROGMEM = "ssid = %s\trssi = %d dBm" EOL;
static const char sta_psk_format[] PROGMEM = "sta_psk = %s" EOL;
static const char err_unknown_cmd_format[] PROGMEM = "ERROR: UNKNOWN COMMAND %s" EOL;

static const char no_access_points_found[] PROGMEM = "no access points found" EOL;
static const char ssid_too_long[] PROGMEM = "SSID_TOO_LONG" EOL;
static const char ssid_too_short[] PROGMEM = "SSID_TOO_SHORT" EOL;
static const char psk_pass_too_long[] PROGMEM = "PSK_PASS_TOO_LONG" EOL;
static const char psk_pass_too_short[] PROGMEM = "PSK_PASS_TOO_SHORT" EOL;

Command cmd_list[] = {
    //command-function pairs
    Command(IDN_cmd, [](const char *a) {
        Serial.printf_P(IDN_format, NG_model.str, NG_version.str, NG_uuid.str);
    }),

    Command(ECHO_cmd, [](const char *a) {
        if (*a == '1')
            echo_on = 1;
        else
            echo_on = 0;
        Serial.printf_P(ECHO_format, echo_on);
    }),

    Command(RST_cmd, [](const char *a) {
        Serial.printf_P(romstr_waiting_for_WDT);
        while (true)
            ; // wait for watchdog timer
    }),

    Command(SCAN_cmd, [](const char *a) {
        int8_t n_NetworksFound = ng_WiFi.scan();
        if (n_NetworksFound == WIFI_SCAN_RUNNING)
        {
            Serial.printf_P(wifi_scan_running);
            return;
        }
        if (n_NetworksFound == WIFI_SCAN_FAILED)
        {
            Serial.printf_P(wifi_scan_failed);
            return;
        }
        if (n_NetworksFound)
        {
            for (int i = 0; i < n_NetworksFound; i++)
                Serial.printf_P(scan_result_format, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
        }
        else
            Serial.printf_P(no_access_points_found);
        WiFi.scanDelete();
    }),

    Command(STA_SSID_cmd, [](const char *a) {
        switch (ng_WiFi.set_STA_SSID(a))
        {
        case SSID_TOO_LONG:
            Serial.printf_P(ssid_too_long);
            break;
        case SSID_TOO_SHORT:
            Serial.printf_P(ssid_too_short);
            break;
        case SSID_OK:
            ng_WiFi.print_sta_ssid();
        }
    }),

    Command(STA_PSK_cmd, [](const char *a) {
        switch (ng_WiFi.set_STA_PSK(a))
        {
        case PSK_PASS_TOO_LONG:
            Serial.printf_P(psk_pass_too_long);
            break;
        case PSK_PASS_TOO_SHORT:
            Serial.printf_P(psk_pass_too_short);
            break;
        case PSK_PASS_OK:
            Serial.printf_P(sta_psk_format, ng_WiFi.get_STA_PSK());
        }
    }),

    Command(CONNECT_cmd, [](const char *a) {
        ng_WiFi.STA_connect();
    }),

    Command(HELP_cmd, HELP_func), //
    Command([](const char *a) {   // error function must be last!
        Serial.printf_P(err_unknown_cmd_format, a);
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