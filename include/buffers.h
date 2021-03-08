/* File buffers.h  */
#ifndef NIAGARA2_BUFFERS_H
#define NIAGARA2_BUFFERS_H

class RW_buffer
{
private:
    char *f_buf;

public:
    RW_buffer(const int &);
    ~RW_buffer();
    const int len;
    char *buf() const { return f_buf; };
};

extern RW_buffer tmp;

#endif /* !NIAGARA2_BUFFERS_H */