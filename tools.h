#ifndef _TOOLS_HPP
#define _TOOLS_HPP
#include<string>
#include<iostream>
namespace tls{
    void memcpy(char* tag,const char* ori,int bytes);
    void memset(char* tag,char c,int bytes);
    void cstr_copy_to_string(std::string& str1,char* str2,int start,int end);
    bool isSame(const char* str1,const char* str2,int begin,int end);
    void show_string(const char* str,int len);
    void show_line();
}
#endif