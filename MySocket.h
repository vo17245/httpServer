#ifndef _MYSOCKET_HPP
#define _MYSOCKET_HPP
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>
namespace msk{
    std::string ExplainErrorCode(int code);
    int CreateWelcomeSocket(int port=80);
    int WaitClient(int welcome_socket);
}
#endif