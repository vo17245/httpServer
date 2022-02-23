#include"Log.h"
Log::Log(){
    data=new char[LOG_MAX_BYTES];
    bytes=0;
}
int Log::save(){
    if(data==nullptr){
        return -1;
    }
    std::string path;
    time_t time_sec;
    time(&time_sec);
    std::string time_str;
    time_str=ctime(&time_sec);
    path=path+"/"+time_str.substr(0,time_str.length()-1);
    FILE* fp;
    fp=fopen(path.c_str(),"w");
    fwrite(data,bytes,1,fp);
    fclose(fp);
    bytes=0;
    return 1;
}
int Log::write(const char* content,int len){
    if(len>LOG_MAX_BYTES){
        return -1;
    }
    int rest_bytes=LOG_MAX_BYTES-bytes;
    if(rest_bytes<len){
        save();
    }
    for(int i=0;i<len;i++){
        data[bytes+i]=content[i];
    }
    return 1;
}
int Log::release(){
    if(data==nullptr){
        return -1;
    }
    delete[] data;
    data=nullptr;
    bytes=0;
    return 1;
}
Log::~Log(){
    release();
}
int Log::isEnough(int pre_bytes){
    if(pre_bytes>LOG_MAX_BYTES){
        return -2;
    }
    if(pre_bytes<=(LOG_MAX_BYTES-bytes)){
        return 1;
    }
    else{
        return -1;
    }
}