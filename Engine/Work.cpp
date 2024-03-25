#include "Work.h"
#include "log.h"
using namespace Yu::plugin;
using namespace Yu::utility;
using func = void (*)(Plugin *);
void Work::append(Plugin *p)
{
    m_libso_objs.push_back(p);
}

bool Work::run(Context &p, const string &libname)
{
    if (get_switch() == false)
        return false;

    // LOGGERDEBUG("%d Work is running\n",m_id);

    if (libname.size() == 0)
    {
        auto it = m_libso_objs.begin();
        for (; it != m_libso_objs.end(); ++it)
        {

            if ((*it)->flag())
            {
                if ((*it)->run(p) == false) // 真实情况 每个work这里都要去一个线程执行任务
                {
                    // log
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        auto it = m_libso_objs.begin();
        for (; it != m_libso_objs.end(); ++it)
        {

            if ((*it)->flag()&&(*it)->libso_name()==libname)
            {
                return (*it)->run(p);
            }
        }
    }
      return false;
}

Work::~Work()
{
    auto it = m_libso_objs.begin();
    for (; it != m_libso_objs.end();)
    {
        func p = (func)single<Plugin_Helper>::instance()->sym((*it)->libso_name(), "destrory");
        Plugin *temp = *it;
        ++it;
        p(temp);
    }
}