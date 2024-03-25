#include"server.h"
#include"Context.h"
#include"Work_Flow.h"
using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::thread;
using namespace Yu::plugin;
 using m= Plugin *(*)();



int main(){

WorkFlow a;

a.load("work.xml");
string out;
a.run(1,"Jame Harden",out,"EchoPlugin.so"
);

//single<Server>::instance()->start();

// Plugin_Helper temp;
// temp.load("EchoPlugin.so");

// void *p= temp.sym("EchoPlugin.so","Create");

//    auto x=(m ) p;

//    Plugin *i=x();

//    i->run();

}