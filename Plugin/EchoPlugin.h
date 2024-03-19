#pragma once
#include"Plugin.h"
using namespace Yu::plugin;
namespace Yu::plugin{
    class EchoPlugin:public Plugin{
        public:
        virtual bool run();
        EchoPlugin()=default;
        ~EchoPlugin()=default;
    };

    
}