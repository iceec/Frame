#include"Task.h"
#include "Socket_Handle.h"
#include<thread>
#include<chrono>
using namespace Yu::thread;
using namespace Yu::socket;
using namespace Yu::utility;

#define MAXREV  1024
void EchoTask::run(){
    Socket temp(m_sockfd);

    char buf[MAXREV]{0};
    int len=temp.recv(buf,MAXREV);

    if(len<=0){
        
       LOGGERDEBUG("%d is close and len is %d\n",m_sockfd,len);
       temp.close();
       is_close=true;
        return ;
    }
    temp.send(buf,len);
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    return ;
}

//这里每一个县城dest都要操作红黑书 所以得家所
  void EchoTask::destory(){
    
    if(is_close)
        single<Socket_Handle>::instance()->detach(m_sockfd);
    else
        single<Socket_Handle>::instance()->mod(m_sockfd);
  
    delete this;
  }


EchoTask::EchoTask():m_sockfd(-1),is_close(false){

}

EchoTask::EchoTask(int fd):m_sockfd(fd),is_close(false){

}