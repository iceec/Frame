#include"Client_Socket.h"
#include<stdio.h>
using namespace Yu::socket;

int main(){
    Client_Socket t1("127.0.0.1",8866);

    char buf[100]{0};

    while(fgets(buf,20,stdin)!=NULL){
            t1.send(buf,strlen(buf));
        int len=strlen(buf);
            for(int i=0;i<len;i++)
                buf[i]=0;
            t1.recv(buf,len);
        printf("mess recv %s \n",buf);
         for(int i=0;i<len;i++)
                buf[i]=0;
    }

    t1.close();
    
}