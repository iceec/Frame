#include"server.h"
#include"Work.h"
using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::thread;
using namespace Yu::plugin;
 using m= Plugin *(*)();
int main(){
//single<Server>::instance()->start();

Work a;

single<Plugin_Helper>::instance()->load("EchoPlugin.so");

void *p=single<Plugin_Helper>::instance()->sym("EchoPlugin.so","create");

m x=(m)p;

a.append(x());

a.run();


// Plugin_Helper temp;
// temp.load("EchoPlugin.so");

// void *p= temp.sym("EchoPlugin.so","Create");

//    auto x=(m ) p;

//    Plugin *i=x();

//    i->run();

}