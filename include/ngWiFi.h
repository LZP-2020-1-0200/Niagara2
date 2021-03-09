/* File ngWiFi.h */
#ifndef NIAGARA2_WIFI_H
#define NIAGARA2_WIFI_H

#include "task.h"

class NG_WiFi : public NG_Task
{
private:
    /* data */
public:
    NG_WiFi(/* args */);
    ~NG_WiFi();
        int exec(const uint32 &new_u);
};
extern NG_WiFi ng_WiFi;
#endif /* NIAGARA2_WIFI_H */