
RM = /bin/rm -f
CP = /bin/cp

CC = g++

CPPFLAGS =  -g -rdynamic -Wall -D_REENTRANT  

# lkj add:
top_path := $(shell pwd | awk -F ' ' {print$1})
dest_outlib_dir := $(top_path)/../outlib
tencent_sdk_lib:=tencent_sdk_lib


export INC_JSON :=-I$(dest_outlib_dir)/jsoncpp/include
export LIB_JSON :=-L$(dest_outlib_dir)/jsoncpp/lib -ljson

export INC_OPENSSL:=-I$(dest_outlib_dir)/openssl/include
export LIB_OPENSSL:=-L$(dest_outlib_dir)/openssl/lib -lssl -lcrypto

export INC_OAUTH:=-I$(dest_outlib_dir)/oauth/include
export LIB_OAUTH:=-L$(dest_outlib_dir)/oauth/lib -loauth

export INC_CURL:=-I$(dest_outlib_dir)/curl/include
export LIB_CURL:=-L$(dest_outlib_dir)/curl/lib  -lcurl

export INC_OPENAPI:=-I$(top_path)/../$(tencent_sdk_lib)/include
export LIB_OPENAPI:=-L$(top_path)/../$(tencent_sdk_lib)/lib -lopenapi


# lkj end

LIBS =  $(LIB_OPENAPI) $(LIB_JSON) $(LIB_OAUTH) $(LIB_CURL) $(LIB_OPENSSL)  -lrt  -ldl
INCL =  $(INC_OPENAPI) $(INC_JSON)  $(INC_OPENSSL) $(INC_OAUTH) $(INC_CURL)   -I./include

SOURCES      := $(wildcard *.cpp)
TARGETS      := $(patsubst %.cpp, %, $(SOURCES))

all: $(TARGETS)

%: %.cpp Makefile
	echo -e "\033[41;36m  INC_OPENAPI = $(INC_OPENAPI) oooooooooooooooooooooooooo \033[0m"	&&\
	echo -e "\033[41;36m  example start oooooooooooooooooooooooooo \033[0m"	&&\
	$(CC)  -o $@  $(CPPFLAGS) $< $(INCL) $(LIBS)

clean:
	$(RM) $(DEPENDS) $(TARGETS)
	$(RM) *.o














