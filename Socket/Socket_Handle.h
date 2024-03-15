#pragma once
#include"Sever_Socket.h"
#include"Event_Poller.h"
#include"Mutex.h"

using namespace Yu::utility;
using namespace Yu::thread;
namespace Yu::socket{

    class Socket_Handle{
            SINGLE(Socket_Handle);

            private:
                Sever_Socket* m_listen;
                EventPoller m_handle;
                Mutex  m_sock_handle_lock; 
            public:
               void  Bind_Listen_Create(const string & ,int port ,int number=1024);
               void attach(int fd);
               void detach(int fd);
               void mod(int fd);
               void handle(int );
               void remove(int fd);

    };


}
