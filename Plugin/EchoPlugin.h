#pragma once
#include"Plugin.h"
using namespace Yu::plugin;
namespace Yu::plugin{
    class EchoPlugin:public Plugin{
        public:
        virtual void run();
        EchoPlugin()=default;
        ~EchoPlugin()=default;
    };

    
}