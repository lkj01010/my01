RM = /bin/rm -f
CP = /bin/CP

CC = g++
CPPFLAGS = -g -O2 -Wall -W \
	-pedantic -ansi


LIB_BOOST = -L/usr/local/lib64/boost_1_58_0/stage/lib
INC_BOOST = -I/usr/local/lib64/boost_1_58_0

# LIBDIR = $(LIB_BOOST)



SRC := $(wildcard \
		com/*.cpp \
		mongodb/*.cpp \
		net/*.cpp \
		net/proto/*.cpp \
		net/proto/http/*.cpp )

INCL =	$(INC_BOOST)	\
		-I./	\
		-I./com \
		-I./mongodb \
 		-I./net \
		-I./net/proto \
		-I./net/proto/http

LIBS = $(LIB_BOOST) -lboost_system -lboost_thread  -lboost_date_time -lboost_log\
	-std=c++11

# OBJS := $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))
OBJS := $(patsubst %.cpp, ../obj/%.o, $(SRC))

# OBJ_com = $(patsubst com/%.cpp, ../obj/com/%.o, $(SRC))
# OBJ_mongodb = $(patsubst mongodb/%.cpp, ../obj/mongodb/%.o, $(SRC))
# OBJ_net = $(patsubst net/%.cpp, ../obj/net/%.o, $(SRC))
# OBJ_net_proto = $(patsubst net/proto/%.cpp, ../obj/net/proto/%.o, $(SRC))

TARGET = ../lib/libmy01.a

all: $(TARGET)

$(TARGET): config $(OBJS)
	ar -rc $(TARGET) $(OBJS)

.PHONY: config
config:
	mkdir -p ../lib
	mkdir -p ../obj
	mkdir -p ../obj/com
	mkdir -p ../obj/mongodb
	mkdir -p ../obj/net
	mkdir -p ../obj/net/proto
	mkdir -p ../obj/net/proto/http

../obj/com/%.o: com/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 
../obj/mongodb/%.o: mongodb/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 
../obj/net/%.o: net/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL)  
../obj/net/proto/%.o: net/proto/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 
../obj/net/proto/http/%.o: net/proto/http/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)