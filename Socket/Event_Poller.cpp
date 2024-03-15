#include "Event_Poller.h"

namespace Yu::socket
{

    EventPoller::EventPoller() : m_epollfd(-1), m_max_conn(-1), m_events(nullptr) {}
    EventPoller::~EventPoller()
    {
        if (m_epollfd > 0)
            ::close(m_epollfd);
        if (m_events != nullptr)
                delete[] m_events;
                
    }

    bool EventPoller::create(int max){
        m_epollfd=::epoll_create(max);
        if(m_epollfd<0){
            LOGGERERROR("cant not create Event_poller\n");
            return false;
        }
            
        m_max_conn=max+1;
        m_events=new struct epoll_event [m_max_conn];
        return true;
    }

    void EventPoller::add(int fd,uint32_t flags){
        struct epoll_event ev;
        ev.events=flags;
        ev.data.fd=fd;
        ::epoll_ctl(m_epollfd,EPOLL_CTL_ADD,fd,&ev);
    }

     void EventPoller::mod(int fd,uint32_t flags){
        struct epoll_event ev;
        ev.events=flags;
        ev.data.fd=fd;
        ::epoll_ctl(m_epollfd,EPOLL_CTL_MOD,fd,&ev);
    }

     void EventPoller::del(int fd){
        ::epoll_ctl(m_epollfd,EPOLL_CTL_DEL,fd,nullptr);
    }
    int EventPoller::wait(int timeout){
        return ::epoll_wait(m_epollfd,m_events,m_max_conn,timeout);
    }

    bool EventPoller::is_set(int idx,uint32_t flags){
        if(idx>=m_max_conn)
            return false;
        return m_events[idx].events & flags;
    }

    int EventPoller::get_fd(int idx){
         if(idx>=m_max_conn)
            return -1;
        return m_events[idx].data.fd;
    }
}