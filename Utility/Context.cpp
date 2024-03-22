#include"Context.h"
#include<cstring>
using namespace Yu::utility;




Context::~Context(){clear();}
Context::Context(){}

void Context::clear(){
    m_bool.clear();
    m_char.clear();
    m_int.clear();
    m_double.clear();
    m_string.clear();

    for(auto p=m_objs.begin();p!=m_objs.end();++p){
            if(p->second)
            {
                delete p->second;
                p->second=nullptr;
            }
    }
    m_objs.clear();
}

  bool Context::get(const string &key, char *buf, int len){
        if(m_string.count(key)){
        int size=m_string.size();
        size=(size>(len-1))?len-1:size;
        memcpy(buf,&(m_string[key][0]),size);
            buf[len-1]=0;
            return true;
        }

        return false;
  }