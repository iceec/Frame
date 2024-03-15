#pragma once
#include<unistd.h>
#include<string>
using std::string;
namespace Yu::utility{

    class System_Path{

        public:
            System_Path();
            ~System_Path()=default;
            string name();
        private:
            string get_path_name();
            string m_work_path;
        
    };

}