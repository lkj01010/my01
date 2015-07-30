vpath %.cpp ./src
RM = /bin/rm -f
CP = /bin/cp

CC = g++
CPPFLAGS = -g  -rdynamic  -Wall -D_REENTRANT

LIBDIR = $(LIB_JSON) $(LIB_OAUTH) $(LIB_CURL) $(LIB_OPENSSL) -ldl -lrt
INCL = $(INC_JSON)  $(INC_OPENSSL) $(INC_OAUTH) $(INC_CURL)  -I./include

SOURCES := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,obj/%.o, $(SOURCES))

TARGET = lib/libopenapi.a

all: $(TARGET)

$(TARGET): $(OBJS)
	echo -e "\033[41;36m  $(TARGET) start oooooooooooooooooooooooooo \033[0m"	&&\
	ar -rc  $(TARGET) $(OBJS)

obj/%.o: src/%.cpp
	echo -e "\033[41;36m  obj/%.o start oooooooooooooooooooooooooo \033[0m"	&&\
	$(CC) -c -o $@ $(CPPFLAGS) $(INCL) $<

clean:
	$(RM) $(OBJS) $(TARGET)
