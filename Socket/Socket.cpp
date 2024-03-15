#include "Socket.h"
// define 学习一下
namespace Yu::socket
{

    Socket::Socket()
    {
        m_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_fd < 0)
        {
            LOGGERERROR("Create Socket error: errno=%d errmsg =%s\n", errno, strerror(errno));
        }
        else
            LOGGERDEBUG("create socket %d success\n",m_fd);
    }


    bool Socket::is_empty() const
    {
        if (m_fd < 0)
            LOGGERERROR("this cokset can't use\n");
        return m_fd < 0;
    }

    bool Socket::bind(int port, const string &ip)
    {
        if (is_empty())
            return false;
        struct sockaddr_in temp;
        std::memset(&temp, 0, sizeof(temp));
        if (ip.size())
            temp.sin_addr.s_addr = inet_addr(ip.c_str()); // 对方
        else
            temp.sin_addr.s_addr = INADDR_ANY;
        temp.sin_family = AF_INET;
        temp.sin_port = htons(port);

        if (::bind(m_fd, (const sockaddr *)(&temp), sizeof(temp)) < 0)
        {
            LOGGERERROR("Bind socket error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return false;
        }

        LOGGERDEBUG("Bind success \n");
        return true;
    }

    bool Socket::listen(int backlog)
    {
        if (is_empty())
            return 0;
        if (::listen(m_fd, backlog) < 0)
        {
            LOGGERERROR("Listen socket error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }

        LOGGERDEBUG("%d is listening...\n", m_fd);
        return 1;
    }

    bool Socket::connect(int port, const string &ip)
    {
        if (is_empty())
            return 0;
        struct sockaddr_in temp;
        std::memset(&temp, 0, sizeof(temp));
        temp.sin_addr.s_addr = inet_addr(ip.c_str());
        temp.sin_family = AF_INET;
        temp.sin_port = htons(port);
        if (::connect(m_fd, (const sockaddr *)&temp, sizeof(temp)) < 0)
        {
            LOGGERERROR("Connect socket error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        LOGGERDEBUG("%d connect success\n", m_fd);
        return true;
    }

    int Socket::accept()
    {
        if (is_empty())
            return -1;

        int temp = ::accept(m_fd, nullptr, nullptr);
        LOGGERDEBUG("%d accept success\n", temp);
        return temp;
    }

    int Socket::send(const char *buf, int len, int option)
    {
        if (is_empty())
            return -1;
        int temp = ::send(m_fd, buf, len, option);
        return temp;
    }
    int Socket::recv(char *buf, int len, int option)
    {
        if (is_empty())
            return -1;
        int temp = ::read(m_fd,buf,len);
        return temp;
    }
    void Socket::close()
    {
        if (is_empty())
            return;
        if(m_fd>0){
            ::close(m_fd);
        LOGGERDEBUG("%d is closed\n", m_fd);
        }
        
    }

    void Socket::clear(){
        m_fd=0;
    }

    bool Socket::setnonblock()
    {
        if (is_empty())
            return 0;
        int flags = fcntl(m_fd, F_GETFL, 0);
        if (flags < 0)
        {
            LOGGERERROR("Get flag error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        flags |= O_NONBLOCK;
        if (fcntl(m_fd, F_SETFD, &flags, sizeof(flags)) < 0)
        {
            LOGGERERROR("Set flag error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        return 1;
    }

    bool Socket::set_send_buffer(int size)
    {
        int temp = size;

        if (is_empty())
            return 0;
        if (setsockopt(m_fd, SOL_SOCKET, SO_SNDBUF, &temp, sizeof(temp)) < 0)
        {
            LOGGERERROR("Send buf size error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        return 1;
    }
    bool Socket::set_recv_buffer(int size)
    {
        int temp = size;

        if (is_empty())
            return 0;
        if (setsockopt(m_fd, SOL_SOCKET, SO_RCVBUF, &temp, sizeof(temp)) < 0)
        {
            LOGGERERROR("Recv buf size error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        return 1;
    }

    bool Socket::set_linger(bool active, int seconds)
    {
        if (is_empty())
            return 0;
        struct linger i;
        std::memset(&i, 0, sizeof(i));
        i.l_onoff = (active) ? 1 : 0;
        i.l_linger = seconds;
        if (setsockopt(m_fd, SOL_SOCKET, SO_LINGER, &i, sizeof(i)) < 0)
        {
            LOGGERERROR("Set_linger error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        return 1;
    }
    bool Socket::set_keepalive()
    {
        if (is_empty())
            return 0;
        int i = 1;
        if (setsockopt(m_fd, SOL_SOCKET, SO_KEEPALIVE, &i, sizeof(i)) < 0)
        {
            LOGGERERROR("Set_keepalive error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        return 1;
    }
    bool Socket::set_reuseaddr()
    { // 允许这个套接字绑定在服用地址
        if (is_empty())
            return 0;
        int i = 1;
        if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) < 0)
        {
            LOGGERERROR("Set_reuseaddr error: errno=%d errmsg =%s\n", errno, strerror(errno));
            return 0;
        }
        return 1;
    }

}
