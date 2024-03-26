#pragma once

#include"Socket_Handle.h"
#include"Thread_Poll.h"
#include"Thread_Dispatch.h"
#include"System_Path.h"
#include"ini_file.h"
#include"Work_Flow.h"
using namespace Yu::socket;
using namespace Yu::utility;
using std::string;
namespace Yu::utility{
    class Server{

        private:
            string m_ip;
            int m_port;
            int m_threads;
            int m_wait_time;
            int m_log_level;
            int m_max_handle;
         
        SINGLE(Server);

        public:
            void start();
            void init();

    };
}