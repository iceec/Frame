#include"Socket_Handle.h"
#include"Thread_Poll.h"
#include"Thread_Dispatch.h"
#include"System_Path.h"
#include"ini_file.h"
#include<iostream>

using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::thread;

int main(){
System_Path sys;

single<ini>::instance()->load(sys.name()+"/Config/server.ini");
auto p= single<ini>::instance();
string ip=(*p)["server"]["ip"];  //服务端这个没啥必要阿
int port=(*p)["server"]["port"];
int threads=(*p)["server"]["threads"];
int wait_time=(*p)["server"]["wait_time"];
int log_level=(*p)["server"]["log_level"];
int max_handle=(*p)["server"]["max_handle"];


single<logger>::instance()->open(sys.name()+"/sever.log");
single<logger>::instance()->setlevel((logger::LEVEL)log_level);
single<Socket_Handle>::instance()->Bind_Listen_Create("",port,max_handle);
single<Thread_Dispatch>::instance()->init(threads);
single<Socket_Handle>::instance()->handle(wait_time);

}