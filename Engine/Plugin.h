#pragma once
#include <string>
#include"Context.h"
using std::string;
using namespace Yu::utility;
namespace Yu::plugin
{

    class Plugin
    {
    public:
        Plugin() : is_on(true) {}

        virtual ~Plugin() = default;
        void set_libso_name(const string &p) { m_libso_name = p; }
        const string &libso_name() { return m_libso_name; }
        void set_flag(bool flags) { is_on = flags; }
        bool flag() { return is_on; }
        virtual bool run(Context &) = 0;

    private:
        string m_libso_name;
        bool is_on;
    };

#define DEFINE_PLUGIN(classname)                 \
    extern "C"                                   \
    {                                            \
        Plugin *create()                         \
        {                                        \
            Plugin *p = new classname();         \
            p->set_libso_name(#classname ".so"); \
            return p;                            \
        }                                        \
        void destrory(Plugin *p)                 \
        {                                        \
            delete p;                            \
            return;                              \
        }                                        \
    }

    // 类中不允许使用C所以每一个都是普通函数 但是为什么可以是因为 需要连接 自己的cpp
}
