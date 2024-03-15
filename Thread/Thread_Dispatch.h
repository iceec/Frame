#pragma once
#include"Task.h"
#include"Thread.h"
#include"log.h"
#include"Mutex.h"
#include"Connditon.h"
#include<list>
using std::list;
using namespace Yu::thread;
using namespace Yu::utility;
namespace Yu::thread{

class Thread_Dispatch:public Thread{
        SINGLE(Thread_Dispatch);

    private:
        list<Task *>m_wait_exc;
        Mutex m_dis_loc;
        Conndtion m_dis_con;

    public:
        void run()override;
        void init(int number_of_workthread);
        void push(Task *);
        //Task* pop();
};


}