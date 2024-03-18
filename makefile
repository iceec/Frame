UtilityCpps:=$(shell find ./Utility -type f | grep '.cpp')
$(info UtilityCpps is $(UtilityCpps))
UtilityObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(UtilityCpps)))
$(info UtilityObjs is $(UtilityObjs))

SocketCpps:=$(shell find ./Socket -type f | grep '.cpp')
$(info SocketCpps is $(SocketCpps))
SocketObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(SocketCpps)))
$(warning SocketObjs is $(SocketObjs))

ThreadCpps:=$(shell find ./Thread -type f | grep '.cpp')
$(info ThreadCpps is $(ThreadCpps))
ThreadObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(ThreadCpps)))
$(info ThreadObjs is $(ThreadObjs))

TaskCpps:=$(shell find ./Task -type f | grep '.cpp')
$(info TaskCpps is $(TaskCpps))
TaskObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(TaskCpps)))
$(info TaskObjs is $(TaskObjs))

FrameCpps:=$(shell find ./Frame -type f | grep '.cpp')
$(info FrameCpps is $(FrameCpps))
FrameObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(FrameCpps)))
$(info FrameObjs is $(FrameObjs))

EngineCpps:=$(shell find ./Engine -type f | grep '.cpp')
$(info FrameCpps is $(EngineCpps))
EngineObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(EngineCpps)))
$(info FrameObjs is $(EngineObjs))

PlugCpps:=$(shell find ./Plugin -type f | grep '.cpp')
$(info PlugCpps is $(PlugCpps))
PlugObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(PlugCpps)))
$(info PlugObjs is $(PlugObjs))
Pluglib :=$(patsubst %.cpp, %.so, $(filter %.cpp, $(PlugCpps)))
$(info Pluglib is $(Pluglib))





# TestFiles=./Test
# SrcFiles=  ./Socket ./Thread ./Utility
 HeaderFiles= ./Socket ./Thread ./Utility ./Task ./Frame ./Plugin ./Engine 
# LibFiles=./lib
# LibSo= lnet

#$(foreach D ,$(LibSo), -$(D)) $(foreach D,$(LibFiles), -L $(D)) 
# DFLAGS = -MP -MD
CFLAGS = -g -O2 -Wall  -Werror -Wno-unused -fPIC -std=c++11 -lpthread -ldl $(foreach D ,$(HeaderFiles),-I$(D))  #静不能share
LFLAGS = -std=c++17 -shared -fPIC -lpthread -ldl -g -O2 -Wall -Werror -Wno-unused  -I./Socket -I./Thread -I./Utility -I./Task -I./Frame -I./Plugin -I ./Engine 



SrcObjs:=$(ThreadObjs) $(SocketObjs) $(UtilityObjs) $(FrameObjs) $(TaskObjs) $(EngineObjs)

s1objs=sever1.o
c1objs=client1.o




s1 :$(SrcObjs) $(s1objs)
	g++ $^ $(CFLAGS) -o $@

c1 :$(SrcObjs) $(c1objs)
	g++ $^ $(CFLAGS) -o $@


%.o:%.cpp
	g++ $^ $(CFLAGS) -c -o $@


lib: $(Pluglib)

%.so:%.cpp
	g++ $^ $(LFLAGS) -o $@


clean:
	rm -f $(SrcObjs) 
cleanlib:
	rm -f $(Pluglib)

libNet:$(SrcObjs) 
	g++ $^ $(CFLAGS) -Wl,-soname,libnet.so.1 -o libnet.so.1.2.3



clib:
	LD_LIBRARY_PATH=/home/baiyu/frame/lib:$LD_LIBRARY_PATH
expo:
	export LD_LIBRARY_PATH



