/* File task.h */
#ifndef NIAGARA2_TASK_H
#define NIAGARA2_TASK_H
#include <Arduino.h>

#define MAX_CMD_LEN 80
#define EOL "\r\n"
void task_addChar(char ch);

class Command
{
private:
    /* data */
public:
    Command(const char *, void (*)(const char *));
    Command(void (*)(const char *)); // display command not found error message

    ~Command(){};
    const char *cmd;
    const size_t cmd_len;
    void (*func)(const char *);
};

#endif /* NIAGARA2_TASK_H */