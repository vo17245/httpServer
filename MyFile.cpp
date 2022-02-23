#include"MyFile.h"
int MyFile::load(char* path){
    FILE* fp=fopen(path,"rb");
    if(fp==nullptr){
        return -1;
    }
    release();
    bytes=fseek(fp,0,SEEK_END);
    data=new char[bytes];
    fread(data,bytes,1,fp);
    fclose(fp);
    return 1;
}
MyFile::MyFile(){
    bytes=0;
    data=nullptr;
}
int MyFile::release(){
    if(data!=nullptr){
        bytes=0;
        delete[] data;
        data=nullptr;
        return 1;
    }
    else{
        return -1;
    }
}
MyFile::~MyFile(){
    release();
}
int MyFile::get_suffix(char* path,char* suffix,int max_len){
    char* p;
    p=path;
    while(*p!=0)p++;
    char* end=p-1;
    while(p!=path&&*p!='.')p--;
    if(p==path){
        return -1;
    }
    char* start=p+1;
    tls::memcpy(suffix,start,end-start+1);
    return 1;
}