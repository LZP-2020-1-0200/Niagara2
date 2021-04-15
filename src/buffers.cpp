#include "buffers.h"

RW_buffer::RW_buffer(const int &L) : len(L)
{
    f_buf = new char[len + 1];
    for (int i = 0; i < len; i++)
        f_buf[i] = 42;
    f_buf[len] = 0;
}
RW_buffer::~RW_buffer()
{
    delete[] f_buf;
}

RW_buffer tmp(80);
RW_buffer tmp2(80);
RW_buffer json_buf(1000);
