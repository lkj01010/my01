RM = /bin/rm -f
CP = /bin/CP

CC = g++
CPPFLAGS = -g -O2 -Wall -W \
	-pedantic -ansi


LIB_BOOST = -L/usr/local/lib/boost_1_58_0/stage/lib
INC_BOOST = -I/usr/local/lib/boost_1_58_0

# LIBDIR = $(LIB_BOOST)



SRC := $(wildcard \
		com/*.cpp \
		mongodb/*.cpp \
		net/*.cpp \
		net/proto/*.cpp)

INCL =	$(INC_BOOST)\
		-I./com \
		-I./mongodb \
 		-I./net \
		-I./net/proto 

LIBS = $(LIB_BOOST) -std=c++11

# OBJS := $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))
OBJS := $(patsubst %.cpp, obj/%.o, $(SRC))

OBJ_com = $(patsubst com/%.cpp, obj/com/%.o, $(SRC))
OBJ_mongodb = $(patsubst mongodb/%.cpp, obj/mongodb/%.o, $(SRC))
OBJ_net = $(patsubst net/%.cpp, obj/net/%.o, $(SRC))
OBJ_net_proto = $(patsubst net/proto/%.cpp, obj/net/proto/%.o, $(SRC))

TARGET = lib/libmy01.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar -rc $(TARGET) $(OBJS)

obj/com/%.o: com/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 
obj/mongodb/%.o: mongodb/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 
obj/net/%.o: net/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL)  
	# -lboost_system  -lboost_filesystem \
	# 	-lboost_thread -lboost_date_time -lboost_timer
obj/net/proto/%.o: net/proto/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LIBS) $(INCL) 


clean:
	$(RM) $(OBJS) $(TARGET)