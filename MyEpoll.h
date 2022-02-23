#ifndef _MYEPOLL_H
#define _MYEPOLL_H
#include<sys/epoll.h>
#define max_events 128
enum EVENT_TYPE{
    event_type_accept,
    event_type_receive
};
struct MY_EVENT_DATA{
    int fd;
    EVENT_TYPE type;
};
class MyEpoll{
    public:
    int epoll_fd;
    struct epoll_event ready_events[max_events];
    int ready_events_num;
    MyEpoll();
    int create(int max_size); 
    int add(int fd,EVENT_TYPE type);
    int del(int fd);
    int wait(int time_out=-1);
};
#endif