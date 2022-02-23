#include"HttpResponse.h"
int HttpResponse::make_header(){
    header.clear();
    header=header+"HTTP/"+version+" "+code+" "+description+"\r\n";
    for(int i=0;i<header_line_name.size();i++){
        header=header+header_line_name[i]+": "+header_line_val[i]+"\r\n";
    }
    header=header+"\r\n";
    return 1;
}
HttpResponse::HttpResponse(){
    body=nullptr;
    body_bytes=0;
}
HttpResponse::~HttpResponse(){
    release_body();
}
int HttpResponse::load_body(std::string path){
    FILE* fp=fopen(path.c_str(),"rb");
    if(fp==nullptr){
        return -1;
    }
    release_body();
    fseek(fp,0,SEEK_END);
    body_bytes=ftell(fp);
    if(body_bytes<=0){
        std::cout<<"error body_bytes=="<<body_bytes<<std::endl;
        std::cout<<path<<std::endl;
        fclose(fp);
        return -2;
    }
    fseek(fp,0,SEEK_SET);
    body=new char[body_bytes];
    fread(body,body_bytes,1,fp);
    fclose(fp);
    header_line_name.push_back("Content-Length");
    header_line_val.push_back(std::to_string(body_bytes));
    header_line_name.push_back("Content-Type");
    std::string content_type;
    path_to_content_type(path,content_type);
    header_line_val.push_back(content_type);
    return 1;
}
int HttpResponse::release_body(){
    if(body==nullptr){
        return -1;
    }
    else{
        delete[] body;
        body=nullptr;
        body_bytes=0;
        return 1;
    }
}
int HttpResponse::clear_header(){
    version.clear();
    code.clear();
    description.clear();
    header_line_name.clear();
    header_line_val.clear();
    return 1;
}
int HttpResponse::path_to_content_type(std::string& path,std::string& content_type){
    auto itor=path.end();
    while(itor!=path.begin()&&*itor!='.')itor--;
    if(itor==path.begin()&&*itor!='.'){
        return -1;
    }
    itor++;
    std::string suffix;
    suffix=path.substr(itor-path.begin(),path.end()-itor);
    if(tls::isSame((char*)suffix.c_str(),"css",0,2)){
        content_type="text/css";
        return 1;
    }
    else if(tls::isSame((char*)suffix.c_str(),"html",0,3)){
        content_type="text/html";
        return 1;
    }
    else if(tls::isSame(suffix.c_str(),"webp",0,3)){
        content_type="image/webp";
        return 1;
    }
    else{
        content_type="application/octet-stream";
        return -2;
    }
}
void HttpResponse::init(){
    version="1.1";
    code="200";
    description="OK";
    header_line_name.clear();
    header_line_val.clear();
}
