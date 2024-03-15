#include "Thread_Dispatch.h"
#include "Thread_Poll.h"
using namespace Yu::utility;
using namespace Yu::thread;

Thread_Dispatch::Thread_Dispatch() : Thread(), m_dis_loc(), m_dis_con() {}

void Thread_Dispatch::init(int number_of_workthread)
{
    start(1, 1);
    LOGGERDEBUG("Thread_Dispatch %ld is start\n", m_id);
    single<Thread_poll>::instance()->init(number_of_workthread);
}

void Thread_Dispatch::run()
{

    while (true)
    {
        m_dis_loc.lock();
        while (m_wait_exc.size() == 0)
            m_dis_con.wait(m_dis_loc);

        if (m_wait_exc.size() == 0)
        {
            m_dis_loc.unlock();
            continue;
        }
        Task *p = m_wait_exc.front();
        m_wait_exc.pop_front();
        m_dis_loc.unlock();
        WorkThread *t = single<Thread_poll>::instance()->pop();
        t->set_task(p);
    }
}

void Thread_Dispatch::push(Task *p)
{
    m_dis_loc.lock();
    m_wait_exc.push_back(p);
    m_dis_loc.unlock();
    m_dis_con.signal();
}

Thread_Dispatch::~Thread_Dispatch(){}