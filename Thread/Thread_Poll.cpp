#include "Thread_Poll.h"

using namespace Yu::thread;
using namespace Yu::utility;

Thread_poll::Thread_poll() : m_poll_Loc(), m_poll_con(), Work_Thread_Num(0)
{
    m_free_Pol.clear();
}

Thread_poll::~Thread_poll() {}

void Thread_poll::init(int number_of_thread)
{
    Work_Thread_Num = number_of_thread;

    for (int i = 0; i < Work_Thread_Num; ++i)
    {

        WorkThread *p = new WorkThread();
        p->start(1, 1);
        m_free_Pol.push_back(p);
        LOGGERDEBUG("Thread %ld is in poll\n", p->get_id());
    }
}

void Thread_poll::push(WorkThread *p)
{
    m_poll_Loc.lock();
    m_free_Pol.push_back(p);
    m_poll_Loc.unlock();
    m_poll_con.signal();
}
WorkThread *Thread_poll::pop()
{

    m_poll_Loc.lock();
    if(m_free_Pol.size()==0)
        LOGGERWARN("Now all Workthread is used, need wait\n");
    while(m_free_Pol.size()==0)
        m_poll_con.wait(m_poll_Loc);

    if(m_free_Pol.size()==0){
        LOGGERERROR("panic  in poll pop\n");
        exit(1);
    }

   WorkThread *p=m_free_Pol.front();
   m_free_Pol.pop_front();
   m_poll_Loc.unlock();
   return p;
}
int Thread_poll::size(){
    m_poll_Loc.lock();
    int temp=m_free_Pol.size();
    m_poll_Loc.unlock();
    return temp;
}

