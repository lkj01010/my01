RM = /bin/rm -f
CP = /bin/CP

CC = g++
CPPFLAGS = -g -O0 -Wall -W -std=c++11 \
	# -D_LINUX	\
	-rdynamic \
	-pedantic -ansi


LIB_BOOST = -L$(BOOST_LIB)
INC_BOOST = -I$(BOOST_INCLUDE)

LIBDIR = $(LIB_BOOST)



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

LIBS = $(LIB_BOOST) -Wl,-Bdynamic  $(LIB_BOOST) -lboost_log -lboost_date_time -lboost_thread -lboost_system   \
		-lrt \
		-ldl
		
	

# OBJS := $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))
OBJS := $(patsubst %.cpp, ../obj/%.o, $(SRC))

# OBJ_com = $(patsubst com/%.cpp, ../obj/com/%.o, $(SRC))
# OBJ_mongodb = $(patsubst mongodb/%.cpp, ../obj/mongodb/%.o, $(SRC))
# OBJ_net = $(patsubst net/%.cpp, ../obj/net/%.o, $(SRC))
# OBJ_net_proto = $(patsubst net/proto/%.cpp, ../obj/net/proto/%.o, $(SRC))

TARGET = ../lib/libmy01.a

all: config  $(TARGET)

$(TARGET): $(OBJS)
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
	echo '$(BOOST_LIB)'
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