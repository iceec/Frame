#pragma once
#include"Task.h"
#include<stdint.h>
using namespace Yu::thread;


namespace Yu::thread{

    const uint16_t MAXRECV=1024;


    struct Meg_Head{
        uint16_t id;
        uint16_t len;
    };

    class Work_Task:public Task{
    public:
        Work_Task()=delete;
        ~Work_Task()=default;
        Work_Task(int sockfd):m_close(false),m_sockfd(sockfd){}
        virtual void run()override;
        virtual void destory()override;
    private:
        bool m_close;
        int m_sockfd;

    };


}