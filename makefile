UtilityCpps:=$(shell find ./Utility -type f | grep '.cpp')
$(info UtilityCpps is $(UtilityCpps))
UtilityObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(UtilityCpps)))
$(info UtilityObjs is $(UtilityObjs))

SocketCpps:=$(shell find ./Socket -type f | grep '.cpp')
$(info SocketCpps is $(SocketCpps))
SocketObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(SocketCpps)))
$(warning SocketObjs is $(SocketObjs))

ThreadCpps:=$(shell find ./Thread -type f | grep '.cpp')
$(info SocketCpps is $(ThreadCpps))
ThreadObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(ThreadCpps)))
$(info SocketObjs is $(ThreadObjs))

TaskCpps:=$(shell find ./Task -type f | grep '.cpp')
$(info SocketCpps is $(TaskCpps))
TaskObjs:=$(patsubst %.cpp, %.o, $(filter %.cpp, $(TaskCpps)))
$(info SocketObjs is $(TaskObjs))




# TestFiles=./Test
# SrcFiles=  ./Socket ./Thread ./Utility
 HeaderFiles= ./Socket ./Thread ./Utility
# LibFiles=./lib
# LibSo= lnet


# DFLAGS = -MP -MD
CFLAGS = -g -O2 -Wall  -Werror -Wno-unused -fPIC -std=c++11 -lpthread -I./Socket  -I./Thread -I./Utility -I./Task  #静不能share
LFLAGS = -std=c++11 -lpthread  -g -O2 -Wall -shared -Werror -Wno-unused  $(foreach D ,$(LibSo), -$(D)) $(foreach D,$(LibFiles), -L $(D)) 



SrcObjs:=$(ThreadObjs) $(SocketObjs) $(UtilityObjs) $(TaskObjs)

s1objs=sever1.o
c1objs=client1.o




s1 :$(SrcObjs) $(s1objs)
	g++ $^ $(CFLAGS) -o $@

c1 :$(SrcObjs) $(c1objs)
	g++ $^ $(CFLAGS) -o $@


%.o:%.cpp
	g++ $^ $(CFLAGS) -c -o $@


clean:
	rm -f $(SrcObjs) 

libNet:$(SrcObjs) 
	g++ $^ $(CFLAGS) -Wl,-soname,libnet.so.1 -o libnet.so.1.2.3



clib:
	LD_LIBRARY_PATH=/home/baiyu/frame/lib:$LD_LIBRARY_PATH
expo:
	export LD_LIBRARY_PATH



