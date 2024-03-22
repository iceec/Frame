#pragma once
#include"Plugin_Helper.h"
#include"Plugin.h"
#include<vector>
using std::vector;
namespace Yu::plugin{

    class Work{
        public:
            Work():m_id(0),m_switch(true){}
            ~Work();
            void append(Plugin *);
            bool get_switch(){return m_switch;}
            void set_switch(bool flags){m_switch=flags;}
            int get_id(){return m_id;}
            void set_id(int id){m_id=id;}
            void run();
        private:
            int m_id;
            bool m_switch;
            vector<Plugin *>m_libso_objs;
    };
}
