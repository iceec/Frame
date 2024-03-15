#include "Connditon.h"

using namespace Yu::thread;

void Conndtion::wait(Mutex &p)
{
    pthread_cond_wait(&m_cond,p.addr());
}
void Conndtion::broadcast()
{
    pthread_cond_broadcast(&m_cond);
}
void Conndtion::signal()
{
    pthread_cond_signal(&m_cond);
}

Conndtion::Conndtion()
{
    pthread_condattr_t condattr;
        pthread_condattr_init(&condattr);
        pthread_cond_init(&m_cond,&condattr);
        pthread_condattr_destroy(&condattr);
}
Conndtion::~Conndtion()
{
    pthread_cond_destroy(&m_cond);
}