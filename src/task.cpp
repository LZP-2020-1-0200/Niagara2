#include "task.h"
#include "Niagara2_generated.h"




typedef struct
{
    const char *cmd;
    const size_t cmd_len;
    void (*func)(const char *);
} cmd_t;

void ERROR_func(const char *args)
{
    Serial.printf_P(PSTR("ERROR: UNKNOWN COMMAND %s\n"), args);
}

static const char pstr_IDN[] PROGMEM = "*IDN?";
void IDN_func(const char *args)
{
    Serial.printf_P(PSTR("uuid = %s\n"), NG_uuid);
}
static const char pstr_HELP[] PROGMEM = "HELP";
void HELP_func(const char *);

static const char pstr_ECHO[] PROGMEM = "ECHO";
void ECHO_func(const char *args)
{
    Serial.printf_P(PSTR("echo = %s\n"), args);
}

cmd_t cmd_list[] = {
    //command-function pairs
    {pstr_IDN, strlen_P(pstr_IDN), IDN_func},    //
                                                 //    {pstr_RST, strlen_P(pstr_RST), RST_func},                      //
    {pstr_HELP, strlen_P(pstr_HELP), HELP_func}, //
                                                 //    {pstr_STA_SSID, strlen_P(pstr_STA_SSID), STA_SSID_func},       //
                                                 //    {pstr_SCAN, strlen_P(pstr_SCAN), SCAN_func},                   //
                                                 //    {pstr_STA_PSK, strlen_P(pstr_STA_PSK), STA_PSK_func},          //
                                                 //    {pstr_CONNECT, strlen_P(pstr_CONNECT), CONNECT_func},          //
                                                 //    {pstr_DISCONNECT, strlen_P(pstr_DISCONNECT), DISCONNECT_func}, //
                                                 //    {pstr_DIAG, strlen_P(pstr_DIAG), DIAG_func},                   //
    {pstr_ECHO, strlen_P(pstr_ECHO), ECHO_func}, //
                                                 //    {pstr_SEND, strlen_P(pstr_SEND), SEND_func},                   //
                                                 //    {pstr_NTP, strlen_P(pstr_NTP), NTP_func},                      //
                                                 //    {pstr_FACTORY, strlen_P(pstr_FACTORY), FACTORY_func},          //
                                                 //    {pstr_LOAD, strlen_P(pstr_LOAD), LOAD_func},                   //
                                                 //    {pstr_SAVE, strlen_P(pstr_SAVE), SAVE_func},                   //
                                                 //    {pstr_ACCESS_KEY, strlen_P(pstr_ACCESS_KEY), ACCESS_KEY_func}, //
    {NULL, 0, ERROR_func}                        //
};

void HELP_func(const char *args)
{
    Serial.println(F("Available commands:"));
    cmd_t *cl = cmd_list;
    for (; cl->cmd; cl++)
    {
        Serial.printf_P("%s\n", cl->cmd);
    }
}

void parse(char *cmd_line, int cmd_line_len)
{
    static char prev_cmd_line[MAX_CMD_LEN + 1] = {'h', 'e', 'l', 'p'};
    static int prev_line_len = 4;
    bool is_new_cmd = true;
    static const char pstr_up_arrow[] PROGMEM = {195, 160, 72, 0};
    if (0 == strncmp_P(cmd_line, pstr_up_arrow, 4))
    {
        is_new_cmd = false;
        cmd_line = prev_cmd_line;
        cmd_line_len = prev_line_len;
    }
    if (cmd_line_len)
    {
        if (is_new_cmd)
        {
            strncpy(prev_cmd_line, cmd_line, cmd_line_len);
            prev_line_len = cmd_line_len;
        }
        cmd_t *cl = cmd_list;
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
        cl->func(&cmd_line[cl->cmd_len]); // this will call cmd_list -> ERROR_func
    }
    else
        Serial.println(F("Empty line"));
}

static bool echo_on = true;
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
        parse(cmd_line, n - 1);
        n = 0;
    }
    if (n >= MAX_CMD_LEN)
    { // buffer overflow
        n = 0;
    }
}
