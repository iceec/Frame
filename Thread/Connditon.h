#pragma once
#include<pthread.h>
#include"Mutex.h"
namespace Yu::thread{


    class  Conndtion{

        public:
        Conndtion();
        ~Conndtion();

        void wait(Mutex &);
        void broadcast();
        void signal();
        private:
            pthread_cond_t m_cond;


    };
}