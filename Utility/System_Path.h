#pragma once
#include<unistd.h>
#include<string>
#include"singleton.h"
using std::string;
namespace Yu::utility{

    class System_Path{

        public:
            
            string path_name();
            void core_dump();
        private:
            string get_path_name();
            string m_work_path;
        SINGLE(System_Path);
        
    };

}