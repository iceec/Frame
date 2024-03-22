
#include "Work_Flow.h"
#include "System_Path.h"
#include <stdexcept>
#include <iostream>
using namespace Yu::plugin;
using namespace Yu::utility;
using std::logic_error;
using create_func = Plugin *(*)();
using std::cout;
using std::endl;
static void f(const string &a) { throw logic_error(a); }

void WorkFlow::load(const string &filename)
{
    string path = single<System_Path>::instance()->path_name() + "/Config/" + filename;
    //cout << path << endl;
    single<Parse>::instance()->load_file(path);
    Xml workflow = single<Parse>::instance()->parse();
    for (auto p = workflow.begin(); p != workflow.end(); ++p)
    {
        int id = p->attr("id");
        if (id <= 0)
            f("attr id wrong\n");
        string is_switch = p->attr("switch");
        Work *temp = new Work();
        temp->set_id(id);
        if (is_switch == "on")
        {
            temp->set_switch(true);
        }
        else if (is_switch == "off")
        {
            temp->set_switch(false);
        }
        else
            f("switch is worong");

        if (m_work_map.count(id))
            f("already has ");
        m_work_map[id] = temp;
        load_plugin(temp, *p);
    }
}

void WorkFlow::load_plugin(Work *work, Xml &elem)
{

    for (auto p = elem.begin(); p != elem.end(); ++p)
    {
        string libname = p->attr("name");
        string is_switch = p->attr("switch");

        single<Plugin_Helper>::instance()->load(libname);
        create_func temp = (create_func)single<Plugin_Helper>::instance()->sym(libname, "create");

        Plugin *objs = temp();
        objs->set_libso_name(libname);

        if (is_switch == "on")
        {
            objs->set_flag(true);
        }
        else if (is_switch == "off")
        {
            objs->set_flag(false);
        }
        else
            f("load pligin");

        work->append(objs);
    }
}

bool WorkFlow::run(int id, const string &input, string &output, const string &libname)
{
    if (m_work_map.count(id) == 0)
        f("run");

    Work *p = m_work_map[id];
    if (p->get_switch() == false)
    {
        // log
        return false;
    }
    if (libname.size() == 0)
    {
        p->run();
        return true;
    }
    //这里的优化是每一个 plugin其实都是有名字的 所以work存储的时候可以名字对应一个map这样指定run的画会有效
    return true;
}