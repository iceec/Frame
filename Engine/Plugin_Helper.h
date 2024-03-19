#pragma once
#include<unordered_map>
#include<dlfcn.h>
#include<string>
#include"singleton.h"
using std::string;
using std::unordered_map;

namespace Yu::plugin{

class Plugin_Helper{

SINGLE(Plugin_Helper);
    public:
    bool load(const string &so_name);
    void unload(const string &so_name);
    void* sym(const string &so_name,const string &func_name);

    private:
        unordered_map<string,void *>m_libso_map; 
};

}
