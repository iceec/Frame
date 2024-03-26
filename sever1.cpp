#include"server.h"
#include"Context.h"
#include"Work_Flow.h"
using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::thread;
using namespace Yu::plugin;




int main(){


single<Server>::instance()->start();


}