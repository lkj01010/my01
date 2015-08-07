vpath %.cpp ./src
RM = /bin/rm -f
CP = /bin/cp

CC = g++
CPPFLAGS = -g -O2 -rdynamic  -Wall -D_REENTRANT

# lkj add:
top_path := $(shell pwd | awk -F ' ' {print$1})
dest_outlib_dir := $(top_path)/../outlib
# tencent_sdk_lib:=tencent_sdk_lib


export INC_JSON :=-I$(dest_outlib_dir)/jsoncpp/include
export LIB_JSON :=-L$(dest_outlib_dir)/jsoncpp/lib -ljson

export INC_OPENSSL:=-I$(dest_outlib_dir)/openssl/include
export LIB_OPENSSL:=-L$(dest_outlib_dir)/openssl/lib -lssl -lcrypto

export INC_OAUTH:=-I$(dest_outlib_dir)/oauth/include
export LIB_OAUTH:=-L$(dest_outlib_dir)/oauth/lib -loauth

export INC_CURL:=-I$(dest_outlib_dir)/curl/include
export LIB_CURL:=-L$(dest_outlib_dir)/curl/lib  -lcurl

# export INC_OPENAPI:=-I$(top_path)/../$(tencent_sdk_lib)/include
# export LIB_OPENAPI:=-L$(top_path)/../$(tencent_sdk_lib)/lib -lopenapi


# lkj end


LIBDIR = $(LIB_JSON) $(LIB_OAUTH) $(LIB_CURL) $(LIB_OPENSSL) -ldl -lrt
INCL = $(INC_JSON)  $(INC_OPENSSL) $(INC_OAUTH) $(INC_CURL)  -I./include

SOURCES := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,obj/%.o, $(SOURCES))

TARGET = lib/libopenapi.a

all: $(TARGET)

$(TARGET): create_dir $(OBJS)
	echo -e "\033[41;36m  $(TARGET) start oooooooooooooooooooooooooo \033[0m"	&&\
	ar -rc  $(TARGET) $(OBJS)

create_dir:
	mkdir -p obj lib   # -p : not error if exsits

obj/%.o: src/%.cpp
	echo -e "\033[41;36m  obj/%.o start oooooooooooooooooooooooooo \033[0m"	&&\
	echo -e "\033[41;36m  incl: $(INCL) \033[0m"	&&\
	$(CC) -c -o $@ $(CPPFLAGS) $(INCL) $<


clean:
	$(RM) $(OBJS) $(TARGET)
