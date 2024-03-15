#pragma once
#include<pthread.h>

namespace Yu::thread{


    class Mutex{
        public:
            Mutex(int flags=PTHREAD_MUTEX_ERRORCHECK);  //
            ~Mutex(){pthread_mutex_destroy(&m_lock);}
            void lock();
            void unlock();
            bool trylock();
            pthread_mutex_t * addr();
        private:
            pthread_mutex_t m_lock;
    };


    class AutoMutex{
        public:
            AutoMutex(Mutex * p1):p(p1){p->lock();}
            ~AutoMutex(){p->unlock();}
        private:
            Mutex * p;
    };
}