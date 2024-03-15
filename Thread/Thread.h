#pragma once
#include<pthread.h>

namespace Yu::thread{

    class Thread{
        public:
        Thread(): m_id(0){}
        virtual ~Thread()=default;

        virtual void run()=0;
    

        void start(bool is_system,bool is_detach);
        void stop();

        protected:
            pthread_t m_id;
        protected:
            static void * Thread_func(void *);

    };

}