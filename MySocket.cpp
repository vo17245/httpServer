#include"MySocket.h"
std::string msk::ExplainErrorCode(int code){
    switch (code)
    {
    case -1:
        return "error: bind failed";
        break;
    case -2:
        return "error: listen failed";
        break;
    case -3:
        return "error: accept failed";
        break;
    default:
        return "unknown error code";
        break;
    }
}
int msk::CreateWelcomeSocket(int port){
    int welcome_socket=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    int server_addr_len=sizeof(server_addr);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    int ret=bind(welcome_socket,(struct sockaddr*)&server_addr,server_addr_len);
    if(ret==-1){
        return -1;
    }
    ret=listen(welcome_socket,10);
    if(ret==-1){
        return -2;
    }
    return welcome_socket;
}
int msk::WaitClient(int welcome_socket){
    struct sockaddr_in client_addr;
    socklen_t client_addr_len=sizeof(client_addr);
    int client_sock=accept(welcome_socket,(struct sockaddr*)&client_addr,&client_addr_len);
    if(client_sock==-1){
        return -3;
    }
    return client_sock;
}