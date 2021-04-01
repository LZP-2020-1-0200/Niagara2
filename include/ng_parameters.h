/* File ng_parameters.h */
#ifndef NIAGARA2_NG_PARAMETERS_H
#define NIAGARA2_NG_PARAMETERS_H
#include "rom_strings.h"

class NG_param
{
private:
    /* data */
public:
    NG_param(/* args */);
    ~NG_param();
    const ROM_Str * path;
};

NG_param::NG_param(/* args */)
{
}

NG_param::~NG_param()
{
}

#endif /* NIAGARA2_NG_PARAMETERS_H */