#pragma once
#include"Thread.h"
#include"Mutex.h"
#include"Connditon.h"
#include"log.h"
#include"Task.h"


namespace Yu::thread{

    class WorkThread:public Thread{
        public:
            virtual void run ()override;    
            pthread_t get_id();
            WorkThread();
            ~WorkThread();
            void set_task(Task *);
            private:
                Mutex m_Wthread_loc;
                Conndtion m_Wthread_con;
                Task * m_Wthread_tas;

        };
}