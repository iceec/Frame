#include"Client_Socket.h"
namespace Yu::socket{
    Client_Socket::Client_Socket(const string &ip,int port):Socket(){
            set_keepalive();
            this->connect(port,ip);
    }
}