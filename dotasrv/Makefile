RM = /bin/rm -f
CP = /bin/CP

CC = g++
LD = g++

CPPFLAGS = -g -O2 -Wall -W  \
	-pedantic -ansi \
	-D_LINUX


LIB_BOOST = -L/usr/local/lib64/boost_1_58_0/stage/lib
INC_BOOST = -I/usr/local/lib64/boost_1_58_0


top_path := $(shell pwd | awk -F ' ' {print$1})
dest_outlib_dir := $(top_path)/openSdk/outlib
tencent_sdk_dir:= $(top_path)/openSdk/tencent_sdk_lib


export INC_JSON :=-I$(dest_outlib_dir)/jsoncpp/include
export LIB_JSON :=-L$(dest_outlib_dir)/jsoncpp/lib -ljson

export INC_OPENSSL:=-I$(dest_outlib_dir)/openssl/include
export LIB_OPENSSL:=-L$(dest_outlib_dir)/openssl/lib -lssl -lcrypto

export INC_OAUTH:=-I$(dest_outlib_dir)/oauth/include
export LIB_OAUTH:=-L$(dest_outlib_dir)/oauth/lib -loauth

export INC_CURL:=-I$(dest_outlib_dir)/curl/include
export LIB_CURL:=-L$(dest_outlib_dir)/curl/lib  -lcurl

export INC_OPENAPI:=-I$(tencent_sdk_dir)/include
export LIB_OPENAPI:=-L$(tencent_sdk_dir)/lib -lopenapi


# LDFLAGS ->lib dir flags   -> L/xxxx
# LIBS -> -lxxx
LIBS =  $(LIB_OPENAPI) $(LIB_JSON) $(LIB_OAUTH) $(LIB_CURL) $(LIB_OPENSSL) \
		-L../lib -lmy01	\
		$(LIB_BOOST) \
		 libboost_system.a libboost_thread.a libboost_log.a libboost_date_time.a  libboost_locale.a libboost_filesystem.a  \
		-std=c++11\
		-lrt \
		 -ldl  

INCL =  $(INC_OPENAPI) $(INC_JSON)  $(INC_OPENSSL) $(INC_OAUTH) $(INC_CURL) \
		$(INC_BOOST) \
		-I../src 
		# ../src/com \
		# ../src/mongodb \
		# ../src/net \
		# ../src/net/proto 


SRC := $(wildcard *.cpp)

# OBJS := $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))
OBJS := $(patsubst %.cpp, ../obj/%.o, $(SRC))

# TARGET = ../bin/dotasrv
TARGET = dotasrv

all: config $(TARGET)

$(TARGET):  $(OBJS)
	$(LD) -o 	$@   $^ $(LIBS) 	 
	# chmod u+x $(TARGET)

config:
	mkdir -p ../obj
	mkdir -p ../bin

../obj/%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 


clean:
	$(RM) $(OBJS) $(TARGET)

# ############
	# ar -rc $(TARGET) $(OBJS) && \
# .mkdir:
#         @if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi