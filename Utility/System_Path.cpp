#include"System_Path.h"
#include"log.h"
#include<sys/resource.h>
using namespace Yu::utility;

string System_Path::get_path_name(){
    char buf[1024]{0};

    int len=readlink("/proc/self/exe",buf,1024);

    if(len<0||len>1024){
            LOGGERERROR("your path is too long \n");
            return "";
    }

    for(int i=len-1;i>=0;--i){
        if(buf[i]=='/'){
            buf[i]=0;
            break;
        }           
    }

    return buf;

}

System_Path::System_Path(){
    m_work_path.clear();
    m_work_path=get_path_name();
    core_dump();
}
System_Path::~System_Path(){}
string System_Path::path_name(){
    return m_work_path;
}
//这个说是处理异常的 但是并不知道有什么用
void System_Path::core_dump(){
    struct rlimit x;
    x.rlim_cur=RLIM_INFINITY;
    x.rlim_max=RLIM_INFINITY;
    setrlimit(RLIMIT_CORE,&x);

    
}