#pragma once
#include"Plugin.h"
#include "Context.h"
using namespace Yu::plugin;
using namespace Yu::utility;
namespace Yu::plugin{
    class EchoPlugin:public Plugin{
        public:
        virtual bool run(Context &)override;
        EchoPlugin()=default;
        ~EchoPlugin()=default;
    };

    
}