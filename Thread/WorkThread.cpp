#include "WorkThread.h"
#include"Thread_Poll.h"
using namespace Yu::thread;
using namespace Yu::utility;
// 工作线程的指针都在线程池当中 所以公共的 数据的
void WorkThread::run()
{
    LOGGERDEBUG("Thread %ld start\n", m_id);
 
    while (true)
    {
        m_Wthread_loc.lock();
        while (m_Wthread_tas == nullptr)
        {
            m_Wthread_con.wait(m_Wthread_loc);
        }
        if (m_Wthread_tas == nullptr)
        {
            LOGGERWARN("this time wake with no tastpointer\n");
            m_Wthread_loc.unlock();
            continue;
        }
        m_Wthread_tas->run();
        m_Wthread_tas->destory();
        m_Wthread_tas = nullptr;
        m_Wthread_loc.unlock();
        single<Thread_poll>::instance()->push(this);
    }
}
pthread_t WorkThread::get_id()
{
    return m_id;
}

WorkThread::WorkThread() : Thread(), m_Wthread_loc(), m_Wthread_con(), m_Wthread_tas(nullptr)
{
}

WorkThread::~WorkThread()
{
}

void WorkThread::set_task(Task *p)
{
    m_Wthread_loc.lock();
    if (m_Wthread_tas != nullptr)
    {
        LOGGERERROR("set task wrong\n");
        m_Wthread_loc.unlock();
        return;
    }
    m_Wthread_tas = p;
    m_Wthread_loc.unlock();
    m_Wthread_con.signal();
    return;
}