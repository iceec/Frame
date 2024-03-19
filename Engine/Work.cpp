#include"Work.h"
#include"log.h"
using namespace Yu::plugin;
using namespace Yu::utility;
using  func = void(*)(Plugin *); 
void Work::append(Plugin * p){
    m_libso_objs.push_back(p);
}


void Work::run(){
    if(get_switch()==false)
        return;

    //LOGGERDEBUG("%d Work is running\n",m_id);
    auto it=m_libso_objs.begin();

    for(;it!=m_libso_objs.end();++it){

        if((*it)->flag()){
            if((*it)->run()==false)   //真实情况 每个work这里都要去一个线程执行任务 
                break;
        }
    }

}

Work::~Work(){
    auto it=m_libso_objs.begin();
    for(;it!=m_libso_objs.end();){
     func p =(func)single<Plugin_Helper>::instance()->sym((*it)->libso_name(),"destrory");
     Plugin *temp= *it;
     ++it;
     p(temp);
   }
}