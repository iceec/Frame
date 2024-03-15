#pragma once
#include "Sever_Socket.h"
#include<sys/epoll.h>

namespace Yu::socket{

    class EventPoller{
        public:

        bool create(int max);
        EventPoller();
        ~EventPoller();
        void add(int fd,uint32_t flags);
        void mod(int fa,uint32_t flags);
        void del(int fd);
        int wait(int timeout=-1);
        bool is_set(int idx,uint32_t flags);
        int get_fd(int idx);
        private:
            int m_epollfd;   
            int m_max_conn;
            struct epoll_event *m_events;//回传的事件
    };
}