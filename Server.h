#ifndef _SERVER_H
#define _SERVER_H
#include<thread>
#include<string>
#include<iostream>
#include<time.h>
#include<thread>
#include"MySocket.h"
#include"tools.h"
#include"MyEpoll.h"
#include"HttpRequest.h"
#include"HttpResponse.h"
#include"Log.h"
#define RECV_BUF_SIZE 1024
#define MAX_ROOT_PATH 128
class Server{
    public:
    char recv_buf[RECV_BUF_SIZE];
    char root_path[MAX_ROOT_PATH];
    int welcome_socket;
    MyEpoll socket_epoll;
    void get_root_path(const char* path,int len);
    int send_response(HttpResponse& response,int client_socket);
    int receive(int client_socket);
    int bad_response(int client_socket);
    std::string url_to_path(std::string& url);
    int go();
    Server();
    Log log;
    int log_write(char* data,int len);
    int log_write(std::string data);
    int log_write(std::string description,char* data,int len);
};
#endif