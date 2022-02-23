#include"HttpRequest.h"
int HttpRequest::GetRequestLine(char* header,int max_len){
    int i=0;
    int j=0;
    while(i<max_len&&header[i]!=' ')i++;
    if(i==max_len){
        return -1;
    }
    tls::cstr_copy_to_string(method,header,0,i-1);
    i++;
    j=i;
    while(i<max_len&&header[i]!=' ')i++;
    if(i==max_len){
        return -1;
    }
    tls::cstr_copy_to_string(url,header,j,i-1);
    i++;
    j=i;
    while(i<max_len&&header[i]!='\r')i++;
    tls::cstr_copy_to_string(version,header,j,i-1);
    i+=2;
    return i;
}
int HttpRequest::GetHeaderLine(char* header,int max_len,int start){
    int i=start;
    int j=start;
    std::string str;
    while(i<max_len){
        if(header[i]=='\r'||header[i]=='\n')return 1;//get all header line 
        while(i<max_len&&header[i]!=' ')i++;
        if(i==max_len)return -1;//illegal format
        tls::cstr_copy_to_string(str,header,j,i-2);
        name.push_back(str);
        str.clear();
        i++;
        j=i;
        while(i<max_len&&header[i]!='\r')i++;
        if(i==max_len)return -1;
        tls::cstr_copy_to_string(str,header,j,i-1);
        val.push_back(str);
        str.clear();
        i+=2;
        j=i;
    }
    return -1;
}
int HttpRequest::analyze_header(char* header,int max_len){
    int start=GetRequestLine(header,max_len);
    if(start==-1){
        return -1;
    }
    int ret=GetHeaderLine(header,max_len,start);
    if(ret==-1)return -1;
    return 1;

}
HttpRequest::HttpRequest(){
    body=nullptr;
    body_length=0;
}
HttpRequest::~HttpRequest(){
    if(body!=nullptr){
        delete[] body;
    }
}
void HttpRequest::clear_header(){
    method.clear();
    url.clear();
    version.clear();
    name.clear();
    val.clear();
}