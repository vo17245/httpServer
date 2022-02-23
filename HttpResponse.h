#ifndef _HTTPRESPONSE_H
#define _HTTPRESPONSE_H
#include<string>
#include<vector>
#include<iostream>
#include"tools.h"
class HttpResponse{
    public:
    std::string version="1.1";
    std::string code="200";
    std::string description="OK";
    std::vector<std::string> header_line_name;
    std::vector<std::string>header_line_val;
    std::string header;
    int make_header();
    char* body;
    int body_bytes;
    int load_body(std::string path);
    int release_body();
    void init();
    int clear_header();
    int path_to_content_type(std::string& path,std::string& content_type);
    HttpResponse();
    ~HttpResponse();
};
#endif