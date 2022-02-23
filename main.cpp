#include<iostream>
#include"tools.h"
#include"MySocket.h"
#include"HttpRequest.h"
#include"Server.h"
#define RECV_BUF_MAXSIZE 1024
int main(int argc,char* argv[]){
    Server server;
    std::string root_path="/home/vo17245/http_server_root";
    server.get_root_path(root_path.c_str(),root_path.length());
    server.go();
    return 0;
}
