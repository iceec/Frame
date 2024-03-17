#include "server.h"
#include <dirent.h>
#include <sys/stat.h>
using namespace Yu::socket;
using namespace Yu::utility;
using std::string;

Server::Server(){}
Server::~Server(){}

void Server::start()
{

    init();
    auto p1 = single<System_Path>::instance();
    single<ini>::instance()->load(p1->name() + "/Config/server.ini");
    auto p = single<ini>::instance();
   // 服务端这个没啥必要阿
    m_port = (*p)["server"]["port"];
    m_threads = (*p)["server"]["threads"];
    m_wait_time = (*p)["server"]["wait_time"];
    m_log_level = (*p)["server"]["log_level"];
    m_max_handle = (*p)["server"]["max_handle"];

single<logger>::instance()->open(p1->name()+"/Log/sever.log");
single<logger>::instance()->setlevel((logger::LEVEL)m_log_level);
single<Socket_Handle>::instance()->Bind_Listen_Create("",m_port,m_max_handle);
single<Thread_Dispatch>::instance()->init(m_threads);
single<Socket_Handle>::instance()->handle(m_wait_time);

}

void Server::init()
{   
    auto p = single<System_Path>::instance();
    string temp = p->name() + "/Log";
    DIR *dp = opendir(temp.c_str());
    if (dp == nullptr)
        mkdir(temp.c_str(), 0755);
    else
        closedir(dp);
}