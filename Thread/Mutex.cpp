#include "Mutex.h"

namespace Yu::thread
{

    Mutex::Mutex(int flags)
    {
        pthread_mutexattr_t m_attr;
        pthread_mutexattr_init(&m_attr);
        pthread_mutexattr_settype(&m_attr, flags);

        pthread_mutex_init(&m_lock, &m_attr);

        pthread_mutexattr_destroy(&m_attr);
    }

    void Mutex::lock()
    {
        pthread_mutex_lock(&m_lock);
    }
    void Mutex::unlock()
    {
        pthread_mutex_unlock(&m_lock);
    }
    bool Mutex::trylock()
    {
        return pthread_mutex_trylock(&m_lock) == 0;
    }

    pthread_mutex_t * Mutex::addr(){
        return &m_lock;
    }
}