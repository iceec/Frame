#include"EchoPlugin.h"
#include<iostream>
using std::cout;
using namespace Yu::plugin;

DEFINE_PLUGIN(EchoPlugin)

bool EchoPlugin::run(Context & p){
       string temp;

     if(p.get("input",temp)){
      cout<<temp<<std::endl;
     }
        cout<<libso_name()<<"\n";
        cout<<"Hello World\n";
        return 1;
}

