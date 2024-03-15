#pragma once
#include"WorkThread.h"
#include<list>
using namespace Yu::thread;
using namespace Yu::utility;
using std::list;
namespace Yu::thread{
    class Thread_poll{


        private:
            list<WorkThread *> m_free_Pol;
            Mutex m_poll_Loc;
            Conndtion m_poll_con;
            int Work_Thread_Num;

            
        SINGLE(Thread_poll);

        public:
            void init(int number_of_thread);
            void push(WorkThread *);
            WorkThread* pop();
            int size();

    };

}
