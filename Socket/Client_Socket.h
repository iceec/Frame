#pragma once
#include"Socket.h"
namespace Yu::socket{
    class Client_Socket:public Socket{
        public :
          Client_Socket()=delete;
          ~Client_Socket()=default;
          Client_Socket(const string &ip,int port);
    };
}