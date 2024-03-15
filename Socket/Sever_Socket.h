#pragma once
#include"Socket.h"

namespace Yu::socket{

    class Sever_Socket:public Socket{

        public :
            Sever_Socket()=delete;
            ~Sever_Socket()=default;
            Sever_Socket(const string &ip,int port,int number=1024);
    };
}