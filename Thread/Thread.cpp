#include "Thread.h"

namespace Yu::thread{



 void Thread::start(bool is_system,bool is_detach){

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    int flag1=(is_system)?PTHREAD_SCOPE_SYSTEM : PTHREAD_SCOPE_PROCESS;
    pthread_attr_setscope(&attr,flag1);
    int flag2=(is_detach)?PTHREAD_CREATE_DETACHED :PTHREAD_CREATE_JOINABLE;
    pthread_attr_setdetachstate(&attr,flag2);
    pthread_create(&m_id,&attr,Thread_func,static_cast<void *>(this));
    pthread_attr_destroy(&attr);
    return ;
 }

 void Thread::stop(){
    pthread_exit(PTHREAD_CANCELED);
 }

 void * Thread::Thread_func(void * p){

    Thread *p1 =static_cast<Thread *>(p);
    p1->run();
    return nullptr;
 }



}