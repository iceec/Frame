#pragma once
#include <string>
using std::string;
namespace Yu::plugin
{

    class Plugin
    {
        public:
        Plugin():is_on(false){};
        virtual ~Plugin() = default;
        void set_libso_name(const string &p){m_libso_name=p;}
        const string & libso_name(){return m_libso_name;}
        void set_flag(bool flags){is_on=flags;}
        bool flag(){return is_on;}
        virtual void run() = 0;
        private:
            string m_libso_name;
            bool is_on;
    };

#define DEFINE_PLUGIN(classname)    \
    extern "C"                      \
    {                               \
        Plugin *Create()            \
        {                           \
            return new classname(); \
        }                           \
        void destrory(Plugin *p)    \
        {                           \
            delete p;               \
            return;                 \
        }                           \
}

// 类中不允许使用C所以每一个都是普通函数 但是为什么可以是因为 需要连接 自己的cpp
}
