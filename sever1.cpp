#include"server.h"
#include"Context.h"
#include"Work_Flow.h"
using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::thread;
using namespace Yu::plugin;
 using m= Plugin *(*)();


 class bb:public Object{
public:
    bb(){};
    ~bb(){};

 };
int main(){
//single<Server>::instance()->start();
auto p=single<Context>::instance();
single<Context>::instance()->set("abc",123);
int a=1;
p->get("abc",a);

Object *pbb=new bb();
cout<<pbb<<endl;
p->set("kl",pbb);

 Object*xx;

p->get("kl",xx);

p->set("anc","asdad");

string t;

p->get("anc",t);

double df=12.32;

p->set("op",df);
double ads;
p->get("op",ads);


std::cout<<a<<" "<<xx<<" "<<t<<" "<<ads;

// Plugin_Helper temp;
// temp.load("EchoPlugin.so");

// void *p= temp.sym("EchoPlugin.so","Create");

//    auto x=(m ) p;

//    Plugin *i=x();

//    i->run();

}