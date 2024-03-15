#pragma once
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include "log.h"
using std::string;
using namespace Yu::utility;
namespace Yu::socket
{

    class Socket
    {
    public:
        Socket();
        ~Socket(){}
        Socket(int fd):m_fd(fd){}

        int fd() const { return m_fd; }
        bool is_empty() const;
        bool bind(int port, const string &ip = "");
        bool listen(int backlog);
        bool connect(int port, const string &ip);
        int accept();
        int send(const char *buf, int len, int option = 0);
        int recv(char *buf, int len, int option = 0);
        void close();
        void clear();

        bool setnonblock();             // fctnl
        bool set_send_buffer(int size); // setsockopt and behind
        bool set_recv_buffer(int size);
        bool set_linger(bool active, int seconds); // if a=0 close发完alldata fin a=1 s=0 close直接发rst a=1 s!=0 close
        // 后在发送 s秒后 然后都发完就fin 没发完rst
        bool set_keepalive(); // 两个小时要是双方没断还没信息 发一个test 没收到断开
        bool set_reuseaddr(); // 自己端的ip和port可以复用 不用等待上一个结束 (仅限于这个套接字)
    private:
        int m_fd;
    };

}