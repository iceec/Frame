#include"Sever_Socket.h"
namespace Yu::socket{
   Sever_Socket::Sever_Socket(const string &ip,int port,int number):Socket(){
        set_keepalive();
        set_linger(1,0);
        set_reuseaddr();
        bind(port,ip);
        listen(number);
   }
}