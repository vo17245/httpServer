#ifndef _LOG_H
#define _LOG_H
#include<string>
#include<time.h>
#define B 1
#define KB 1024*B
#define M 1024*KB
#define LOG_MAX_BYTES 32*KB
class Log{
    public:
    std::string path;
    char* data;
    unsigned bytes;
    Log();
    int save();
    int write(const char* content,int len);
    int release();
    ~Log();
    int isEnough(int pre_bytes);
};
#endif