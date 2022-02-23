#include"MyEpoll.h"
int MyEpoll::create(int max_size){
    epoll_fd=epoll_create(max_size);
    if(epoll_fd>=0){
        return 1;
    }
    else{
        return -1;
    }
}
MyEpoll::MyEpoll(){
    epoll_fd=-1;
}
int MyEpoll::add(int fd,EVENT_TYPE type){
    struct MY_EVENT_DATA* p_event_data=new MY_EVENT_DATA;
    p_event_data->fd=fd;
    p_event_data->type=type;
    struct epoll_event event;
    event.data.ptr=p_event_data;
    event.events=EPOLLIN;
    int ret=epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&event);
    if(ret==0){
        return 1;
    }
    else{
        return -1;
    }
}
int MyEpoll::del(int fd){
    struct epoll_event event;
    event.data.fd=fd;
    event.events=0;
    int ret=epoll_ctl(epoll_fd,EPOLL_CTL_DEL,fd,&event);
    if(ret==0){
        return 1;
    }
    else{
        return -2;
    }
}

int MyEpoll::wait(int time_out){
    ready_events_num=epoll_wait(epoll_fd,ready_events,max_events,time_out);
    if(ready_events_num==-1){
        ready_events_num=0;
        return -1;
    }
    return 1;
}