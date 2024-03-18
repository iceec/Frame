#include"server.h"
#include"Plugin_Helper.h"
#include"Plugin.h"
using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::thread;
using namespace Yu::plugin;
 using m= Plugin *(*)();
int main(){
single<Server>::instance()->start();
// Plugin_Helper temp;
// temp.load("EchoPlugin.so");

// void *p= temp.sym("EchoPlugin.so","Create");

//    auto x=(m ) p;

//    Plugin *i=x();

//    i->run();

}