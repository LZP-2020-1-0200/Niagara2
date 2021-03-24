#include "task.h"
#include "Niagara2_generated.h"

Command::Command(const char *cmd_str, void (*ptr_func)(const char *)) //
    : cmd(cmd_str),
      cmd_len(strlen_P(cmd_str)),
      func(ptr_func)
{
}

void HELP_func(const char *); // implementation requires cmd_list, see below
static int echo_on = 1;

Command cmd_list[] = {
    //command-function pairs
    Command("*IDN?", [](const char *a) {
        Serial.printf("uuid = %s\n", NG_uuid);
    }),
    Command("ECHO", [](const char *a) {
        if (*a == '1')
            echo_on = 1;
        else
            echo_on = 0;
        Serial.printf("echo = %d\n", echo_on);
    }),
    Command("*RST", [](const char *a) {
        Serial.println("waiting for WDT ...");
        while (true)
            ;
    }),
    Command("HELP", HELP_func),     //
    Command("", [](const char *a) { // empty string must be last!
        Serial.printf_P("ERROR: UNKNOWN COMMAND %s\n", a);
    }) // empty string must be last!
};

void HELP_func(const char *args)
{
    Serial.println(F("Available commands:"));
    Command *cl = cmd_list;
    for (; cl->cmd_len; cl++)
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
        //        cmd_t *cl = cmd_list;
        Command *cl = cmd_list;
        int cmd_num = 0;
        //        for (; cl->cmd; cl++)
        for (; cl->cmd_len; cl++)
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
