RM = /bin/rm -f
CP = /bin/CP

CC = g++
LD = g++

CPPFLAGS = -std=c++11  -D_REENTRANT  -W -funroll-loops  \
	-pedantic -ansi 


LIB_BOOST = -L$(BOOST_LIB)
INC_BOOST = -I$(BOOST_INCLUDE)


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
# LIBS =  $(LIB_OPENAPI) $(LIB_JSON) $(LIB_OAUTH) $(LIB_CURL) $(LIB_OPENSSL) \
LIBS = 		-L../lib \
		$(LIB_BOOST) \
		# $(BOOST_LIB)/libboost_system.a \
		# $(BOOST_LIB)/libboost_thread.a \
		# $(BOOST_LIB)/libboost_date_time.a \
		# $(BOOST_LIB)/libboost_locale.a \
		# $(BOOST_LIB)/libboost_filesystem.a \
		# $(BOOST_LIB)/libboost_log.a \
		-std=c++11 \
		-lboost_system -lboost_thread  -lboost_date_time  -lboost_locale -lboost_filesystem -lboost_log \
		-lmy01	\
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
	$(LD)   -o $@   $(CPPFLAGS)	$(LIBS)   $^  	 
	# chmod u+x $(TARGET)

config:
	mkdir -p ../obj
	mkdir -p ../bin

../obj/%.o: %.cpp
	$(CC) -std=c++11 -c -o $@ $(CPPFLAGS) $(LIBS) $(INCL) $<  


clean:
	$(RM) $(OBJS) $(TARGET)

# ############
	# ar -rc $(TARGET) $(OBJS) && \
# .mkdir:
#         @if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi