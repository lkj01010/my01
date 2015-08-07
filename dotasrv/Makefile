RM = /bin/rm -f
CP = /bin/CP

CC = g++
LD = g++

# !!!!!!!!!!!!!!!!!!!!
# 这里必须要有  -W 禁止 所有 警告訊息.（有些头文件会有#error xxxxx 直接包括，但那只是（有
# 的是版本警告）只是人为警告成错误，但不是真正的错误
# -Wall 这是编译器的警告开关，这是真正的潜在错误（编译器给出的）
CPPFLAGS = -g -O2 -Wall -W -std=c++11 \
	 -D_LINUX	
	# -rdynamic \
	# -pedantic -ansi


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
LIB_SDK =  $(LIB_OPENAPI) $(LIB_JSON) $(LIB_OAUTH) $(LIB_CURL) $(LIB_OPENSSL) \

LIBS := -L../lib -Wl,-Bstatic -lmy01 \
		$(LIB_BOOST) \
		-Wl,-Bdynamic  -lboost_system  -lboost_filesystem -lboost_thread  -lboost_date_time  -lboost_locale -lboost_chrono -lboost_regex  -lboost_log  \
		$(LIB_SDK) \
		-lrt \
		-ldl  

		# -Wl,-Bdynamic  -lboost_system -lboost_iostreams  -lboost_log -lboost_regex   -lboost_date_time  -lboost_locale -lboost_chrono -lboost_filesystem -lboost_thread\

# LIBS = -L../lib -lmy01

# LIBS = -lboost_log   -lboost_date_time  -lboost_locale -lboost_filesystem -lboost_thread -lboost_system 

# LIBS = -L../lib \
# 		$(LIB_BOOST) \
# 		-lboost_date_time \
# 		-lmy01	\
# 		-lboost_log   -lboost_date_time  -lboost_locale -lboost_filesystem -lboost_thread -lboost_system \
# 		-lrt \
# 		 -ldl 


		  		# $(BOOST_LIB)/libboost_system.a \
		# $(BOOST_LIB)/libboost_thread.a \
		# $(BOOST_LIB)/libboost_date_time.a \
		# $(BOOST_LIB)/libboost_locale.a \
		# $(BOOST_LIB)/libboost_filesystem.a \
		# $(BOOST_LIB)/libboost_log.a \

INCL =  $(INC_OPENAPI) $(INC_JSON)  $(INC_OPENSSL) $(INC_OAUTH) $(INC_CURL) \
		$(INC_BOOST) \
		-I../src \
		-I../src/com \
		-I../src/mongodb \
		-I../src/net \
		-I../src/net/proto \
		-I../src/net/proto/http


SRC := $(wildcard *.cpp)

# OBJS := $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))
# OBJS := $(patsubst %.cpp, ../obj/%.o, $(SRC))
OBJS := ../obj/main.o ../obj/tencent_api.o

# TARGET = ../bin/dotasrv
TARGET = dotasrv

all: config $(TARGET)

$(TARGET):  $(OBJS) 
	echo -e "\033[41;36m  $(LIBS) TARGET start oooooooooooooooooooooooooo \033[0m"	&&\
	$(LD)   -o $@  $^  $(CPPFLAGS)	$(LIBS)   	 
	chmod u+x $(TARGET)

config:
	mkdir -p ../obj
	mkdir -p ../bin


# ../obj/%.o: %.cpp 
# 	echo -e "\033[41;36m  obj compiler start oooooooooooooooooooooooooo \033[0m"	&&\
# 	$(CC) -c -o $@ $(CPPFLAGS) $(LIBS) $(INCL) $<  

../obj/main.o: main.cpp
	echo -e "\033[41;36m  main compiler start oooooooooooooooooooooooooo \033[0m"	&&\
	$(CC) -c -o $@ $(CPPFLAGS) $(LIBS) $(INCL) $<  
../obj/tencent_api.o: tencent_api.cpp
	echo -e "\033[41;36m  tencent_api compiler start oooooooooooooooooooooooooo \033[0m"	&&\
	$(CC) -c -o $@ $(CPPFLAGS) $(LIBS) $(INCL) $<  


clean:
	$(RM) $(OBJS) $(TARGET)

# ############
	# ar -rc $(TARGET) $(OBJS) && \
# .mkdir:
#         @if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
