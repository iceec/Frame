#include"Client_Socket.h"
#include "Work_Task.h"
#include<stdint.h>
#include<stdio.h>
using namespace Yu::socket;
using namespace Yu::thread;
int main(){
    Client_Socket t1("127.0.0.1",8866);

    char buf[100]{0};
    Meg_Head a;
    a.id=1;
    
    while(fgets(buf,100,stdin)!=NULL){
        a.len=(uint16_t)(strlen(buf));
    std::cout<<a.len<<std::endl;


        t1.send((char *)&a,sizeof(a));
        t1.send(buf,strlen(buf));
        int len=strlen(buf);
            for(int i=0;i<len;i++)
                buf[i]=0;
    }
    t1.close();
    
}