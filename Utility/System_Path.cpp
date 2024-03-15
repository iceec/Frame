#include"System_Path.h"
#include"log.h"
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
}

string System_Path::name(){
    return m_work_path;
}