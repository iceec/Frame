#include"EchoPlugin.h"
#include<iostream>
using std::cout;
using namespace Yu::plugin;

DEFINE_PLUGIN(EchoPlugin)

void EchoPlugin::run(){
        cout<<"Hello World\n";
}