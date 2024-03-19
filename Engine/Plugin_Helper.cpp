#include "Plugin_Helper.h"
#include "System_Path.h"
#include "log.h"

using namespace Yu::plugin;
using namespace Yu::utility;

bool Plugin_Helper::load(const string &so_name)
{

    if (so_name.size() == 0)
    {
        LOGGERERROR("so_name is empty\n");
        return false;
    }
    if (m_libso_map.count(so_name))
        return true;
    string path = single<System_Path>::instance()->path_name() + "/Plugin/" + so_name;

    void *p = dlopen(path.c_str(), RTLD_GLOBAL | RTLD_LAZY);
    if (p == nullptr)
    {
        LOGGERERROR("%s can't open %s\n", so_name, dlerror());
        return false;
    }
    m_libso_map[so_name] = p;
    return true;
}
void Plugin_Helper::unload(const string &so_name)
{
    if (so_name.size() == 0 || m_libso_map.count(so_name) == 0)
    {
        return;
    }

    dlclose(m_libso_map[so_name]);

    m_libso_map.erase(so_name);
}
void *Plugin_Helper::sym(const string &so_name, const string &func_name)
{

    if (load(so_name) == false)
    {
        return nullptr;
    }

    void *p = dlsym(m_libso_map[so_name], func_name.c_str());

    if (p == nullptr)
    {
        LOGGERERROR("%s soname has fuc wrong\n %s\n", so_name, dlerror());
    }

    return p;
}

Plugin_Helper::Plugin_Helper(){}

Plugin_Helper::~Plugin_Helper(){}