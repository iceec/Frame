#include "Socket_Handle.h"
#include "Task.h"
#include "WorkThread.h"
#include"Thread_Dispatch.h"
using namespace Yu::socket;
using namespace Yu::thread;
#define MAXREV 1024
Socket_Handle::Socket_Handle() : m_listen(nullptr), m_handle(), m_sock_handle_lock() {}

Socket_Handle::~Socket_Handle()
{
    if (m_listen)
        delete m_listen;
}
void Socket_Handle::Bind_Listen_Create(const string &ip, int port, int number)
{
    if (m_listen)
    {
        LOGGERERROR("already create socket_handle\n");
        return;
    }
    m_listen = new Sever_Socket(ip, port, number);
    m_handle.create(number);
    m_handle.add(m_listen->fd(), EPOLLIN | EPOLLERR | EPOLLHUP);
}

void Socket_Handle::attach(int fd)
{
    m_sock_handle_lock.lock();
    m_handle.add(fd, EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLONESHOT);
    m_sock_handle_lock.unlock();
}

void Socket_Handle::detach(int fd)
{
    m_sock_handle_lock.lock();
    m_handle.del(fd);
    m_sock_handle_lock.unlock();
}

void Socket_Handle::mod(int fd)
{
    m_sock_handle_lock.lock();
    m_handle.mod(fd, EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLONESHOT);
    m_sock_handle_lock.unlock();
}
void Socket_Handle::remove(int fd)
{
   
    detach(fd);
    Socket temp(fd);
    temp.close();
}



 void Socket_Handle::handle(int wait_time)
 {
     while (true)
     {

         int nums = m_handle.wait(wait_time);

         for (int i = 0; i < nums; ++i)
         {
             int fd = m_handle.get_fd(i);

             if (fd == m_listen->fd())
             {
                if(m_handle.is_set(i,EPOLLERR | EPOLLHUP)){
                        LOGGERERROR("Listen is error\n");
                        exit(1);
                }
                 int temp = m_listen->accept();
                 attach(temp);
             }
             else
             {
                if(m_handle.is_set(i,EPOLLERR | EPOLLHUP)){
                    remove(fd);
                    continue;
                }
             Task *p= new EchoTask(fd);
             single<Thread_Dispatch>::instance()->push(p);

             }
         }
     }
 }
 