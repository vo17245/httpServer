#include"tools.h"
void tls::memcpy(char* tag,const char* ori,int bytes){
    for(int i=0;i<bytes;i++){
        tag[i]=ori[i];
    }
}
void tls::memset(char* tag,char c,int bytes){
    for(int i=0;i<bytes;i++){
        tag[i]=c;
    }
}
void tls::cstr_copy_to_string(std::string& str1,char* str2,int start,int end){
    for(int i=start;i<=end;i++){
        str1+=str2[i];
    }
}
bool tls::isSame(const char* str1,const char* str2,int begin,int end){
    for(int i=begin;i<=end;i++){
        if(str1[i]!=str2[i]){
            return 0;
        }
    }
    return 1;
}
void tls::show_string(const char* str,int len){
    for(int i=0;i<len;i++){
        printf("%c",str[i]);
    }
}
void tls::show_line(){
    std::cout<<__LINE__<<std::endl;
}
