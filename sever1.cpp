#include"server.h"
using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::thread;
int main(){
single<Server>::instance()->start();

}