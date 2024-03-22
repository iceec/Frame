#include"EchoPlugin.h"
#include<iostream>
using std::cout;
using namespace Yu::plugin;

DEFINE_PLUGIN(EchoPlugin)

bool EchoPlugin::run(){
        cout<<libso_name()<<"\n";
        cout<<"Hello World\n";
        return 1;
}