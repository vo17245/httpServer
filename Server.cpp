#include"Server.h"
void Server::get_root_path(const char* path,int len){
    if(len>MAX_ROOT_PATH){
        std::cout<<"illegal root path"<<std::endl;
        exit(-1);
    }
    tls::memset(root_path,0,MAX_ROOT_PATH);
    tls::memcpy(root_path,path,len);
    log.path="/home/vo17245/http_server";
}
int Server::go(){
    log_write("server start");
    bool is_request_compelete;
    socket_epoll.create(1024);
    welcome_socket=msk::CreateWelcomeSocket();
    if(welcome_socket<0){
        std::cout<<msk::ExplainErrorCode(welcome_socket)<<std::endl;
        log_write(msk::ExplainErrorCode(welcome_socket));
        exit(-1);
    }
    socket_epoll.add(welcome_socket,event_type_accept);
    struct MY_EVENT_DATA* p_my_event_data;
    HttpRequest request;
    HttpResponse response;
    while(true){
        log_write("start wait event");
        socket_epoll.wait();
        for(int i=0;i<socket_epoll.ready_events_num;i++){
            p_my_event_data=(struct MY_EVENT_DATA*)socket_epoll.ready_events[i].data.ptr;
            if(p_my_event_data->type==event_type_accept){
                log_write("get a connect event");
                int client_socket=msk::WaitClient(welcome_socket);
                socket_epoll.add(client_socket,event_type_receive);
            }
            else if(p_my_event_data->type==event_type_receive){
                int recv_bytes=receive(p_my_event_data->fd);
                if(recv_bytes<=0){
                    log_write("get a disconnect event");
                    socket_epoll.del(p_my_event_data->fd);
                    close(p_my_event_data->fd);
                    delete p_my_event_data;
                }
                else{
                    int is_response_compelete=request.analyze_header(recv_buf,recv_bytes);
                    if(is_request_compelete==-1){
                        bad_response(p_my_event_data->fd);
                        log_write("get a bad request\r\ncontent: ",recv_buf,recv_bytes);
                    }
                    else{
                        int is_file_exist=response.load_body(url_to_path(request.url));
                        if(is_file_exist==-1){
                            bad_response(p_my_event_data->fd);
                            log_write("can not find the file in request\r\nurl: ",recv_buf,recv_bytes);
                        }
                        else if(is_file_exist==-2){
                            tls::show_string(recv_buf,recv_bytes);
                        }
                        else{
                            log_write("get a good http request\r\ncontent: ",recv_buf,recv_bytes);
                            response.make_header();
                            send_response(response,p_my_event_data->fd);             
                            log_write("send a response\r\nresponse header: ",(char*)response.header.c_str(),response.header.length());
                        }
                    }
                    
                }
                
            }
            response.init();
            request.clear_header();
        }
    }
    return 0;
}
int Server::send_response(HttpResponse& response,int client_socket){
    send(client_socket,response.header.c_str(),response.header.length(),0);
    if(response.body_bytes==0){
        return 1;
    }
    send(client_socket,response.body,response.body_bytes,0);
    return 1;
}
int Server::receive(int client_socket){
    return recv(client_socket,recv_buf,RECV_BUF_SIZE,0);
}
int Server::bad_response(int client_socket){
    HttpResponse response;
    std::string body_path;
    body_path=body_path+root_path+"/base_response/404.html";
    response.load_body((char*)body_path.c_str());
    response.make_header();
    send_response(response,client_socket);
    return 1;
}
std::string Server::url_to_path(std::string& url){
    std::string path;
    path=root_path+url;
    auto itor=url.end();
    itor--;
    if(*itor=='/'){
        path=path+"index.html";
    }
    return path;
}
Server::Server(){
}
int Server::log_write(char* data,int len){
    time_t time_sec;
    time(&time_sec);
    std::string time_str;
    time_str=ctime(&time_sec);
    int ret=log.isEnough(time_str.length()+len);
    if(ret==-2){
        return -1;
    }
    else if(ret==-1){
        log.save();
    }
    log.write(time_str.c_str(),time_str.length());
    log.write(data,len);
    return 1;
}
int Server::log_write(std::string data){
    time_t time_sec;
    time(&time_sec);
    std::string time_str;
    time_str=ctime(&time_sec);
    int ret=log.isEnough(time_str.length()+data.length());
    if(ret==-2){
        return -1;
    }
    else if(ret==-1){
        log.save();
    }
    log.write(time_str.c_str(),time_str.length());
    log.write(data.c_str(),data.length());
    return 1;
}
int Server::log_write(std::string description,char* data,int len){
    time_t time_sec;
    time(&time_sec);
    std::string time_str;
    time_str=ctime(&time_sec);
    int ret=log.isEnough(time_str.length()+description.length()+len);
    if(ret==-2){
        return -1;
    }
    else if(ret==-1){
        log.save();
    }
    log.write(time_str.c_str(),time_str.length());
    log.write(description.c_str(),description.length());
    log.write(data,len);
    return 1;
}