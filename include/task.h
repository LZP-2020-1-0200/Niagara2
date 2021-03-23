/* File task.h */
#ifndef NIAGARA2_TASK_H
#define NIAGARA2_TASK_H
#include <Arduino.h>

#define MAX_CMD_LEN 80
void task_addChar(char ch);

class Command
{
private:
    /* data */
public:
    Command(/* args */);
    ~Command();
        const char *cmd;
    const size_t cmd_len;
    void (*func)(const char *);

};

Command::Command(/* args */)
{
}

Command::~Command()
{
}




#endif /* NIAGARA2_TASK_H */