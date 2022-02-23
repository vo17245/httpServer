#ifndef _MYFILE_H
#define _MYFILE_H
#include<iostream>
#include"tools.h"
class MyFile{
    public:
    int load(char* path);
    char* data;
    unsigned bytes;
    int release();
    int get_suffix(char* path,char* suffix,int max_len);
    MyFile();
    ~MyFile();
};
#endif