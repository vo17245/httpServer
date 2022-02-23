#ifndef _HTTPREQUEST_H
#define _HTTPREQUEST_H
#include<string>
#include<vector>
#include"tools.h"
class HttpRequest{
    public:
    std::string method;
    std::string url;
    std::string version;
    std::vector<std::string> name;
    std::vector<std::string> val;
    char* body;
    unsigned body_length;
    HttpRequest();
    ~HttpRequest();
    int GetRequestLine(char* header,int max_len);
    int GetHeaderLine(char* header,int max_len,int start);
    int analyze_header(char* header,int max_len);
    void clear_header();
};
#endif